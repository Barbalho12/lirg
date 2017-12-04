#ifndef _DIELECTRIC_H_
#define _DIELECTRIC_H_
#include "material.h"
#include "object.h"
#include <math.h>

class Dielectric : public Material{
	public:

		vec3 albedo;
		float rd;

		Dielectric(const vec3 &attenuation, float rd_){
			albedo = attenuation;
			rd = rd_;
		}

		float rSchlick2(const vec3 &normal, const vec3 &incident, float n1, float n2) const{
			float r0 = (n1 - n2)/(n1 + n2);
			r0 *= r0;
			float cosX = -dot(normal, incident);

			if(n1 > n2){
				const float n = n1/n2;
				const float sinT2 = n * n * (1.0 - cosX * cosX);
				
				if(sinT2 > 1.0){
					return 1.0;
				}

				cosX = sqrt(1.0 - sinT2);
			}

			const float x = 1.0 - cosX;
			return r0 + (1.0 - r0) * x * x * x * x * x;
		}

		bool refract(const vec3 &normal, const vec3 &incident, vec3 &refractedRay, float n1, float n2) const{
			const float n = n1 / n2;
			const float cosI = -dot(normal, incident);
			const float sinT2 = n * n * (1.0 - cosI * cosI);
			const float cosT = sqrt(1.0 -sinT2);

			if (sinT2 > 1.0){
				return false;
			}else{
				refractedRay = n * incident + (n * cosI - cosT) * normal;
				return true;
			}
		}

		float reflectance(const vec3 &normal, const vec3 &incident, float n1, float n2) const{
			const float n = n1 / n2;
			const float cosI = -dot(normal, incident);
			const float sinT2 = n * n * (1.0 - cosI * cosI);

			if (sinT2 > 1.0){
				return 1.0;
			}

			const float cosT = sqrt(1.0 - sinT2);
			const float r0rth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
			const float rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
			return (r0rth * r0rth + rPar * rPar)/2.0;
		}
		
		vec3 reflect(const vec3 &normal, const vec3 &incident) const{
			return incident + 2 * -dot(normal, incident) * normal;
		}

		bool scatter(const Ray &r, const HitRecord &ht, vec3 &attenuation, Ray &scattered) const {
			(void) (r);

			vec3 refractedRay;
			vec3 outward_normal;
			vec3 reflectedRay = reflect(ht.normal, r.get_direction());
			attenuation = albedo;
			float reflectProb;
			float ni_over_nt;

			float d = dot(r.get_direction(), ht.normal);

			if(d > 0){
				outward_normal = -ht.normal;
				ni_over_nt = rd;

			}else{
				outward_normal = ht.normal;
				ni_over_nt = 1.0/rd;
			}

			if(refract(outward_normal, r.get_direction(), refractedRay, 1.0, ni_over_nt)){
				reflectProb = rSchlick2(ht.normal, r.get_direction(), 1.0, ni_over_nt);
			}else{
				scattered = Ray(ht.origin, reflectedRay);
				return true;
			}

			if(reflectance(outward_normal, r.get_direction(), 1.0, ni_over_nt) < reflectProb){
				scattered = Ray(ht.origin, reflectedRay);
			}else{
				scattered = Ray(ht.origin, refractedRay);
			}

			return true;
		}
};

#endif