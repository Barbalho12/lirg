#ifndef _METAL_H_
#define _METAL_H_
#include "material.h"
#include "object.h"

class Metal : public Material{
	public:
		vec3 albedo;
		vec3 ambient;
		vec3 specular;
		float shininess;

		Metal(const vec3 &attenuation){
			albedo = attenuation;
		}

		Metal(const vec3 &attenuation, vec3 & ambient_, vec3 & specular_, float shininess_){
			albedo = attenuation;
			ambient = ambient_;
			specular = specular_;
			shininess = shininess_;
		}

		vec3 reflect(const vec3 &v, const vec3 &n) const{
			return v - 2*dot(v,n)*n;
		}
			
		bool scatter(const Ray &r, const HitRecord &ht, vec3 & attenuation, Ray &scattered) const {
			vec3 reflected = reflect(unit_vector(r.get_direction()), ht.normal);
			scattered = Ray(ht.origin, reflected);
			attenuation = albedo;
			return (dot(scattered.get_direction(), ht.normal) > 0);
		}
};

#endif