#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_
#include "material.h"
#include "object.h"
#include "texture.h"

class Lambertian : public Material{
	public:
		vec3 albedo;
		texture *albedo_;

		vec3 ambient;
		vec3 specular;
		float shininess;
		bool textureEnable;
		
		// Lambertian(const vec3 &attenuation, vec3 & ambient_, vec3 & specular_, float shininess_){
		// 	albedo = attenuation;
		// 	ambient = ambient_;
		// 	specular = specular_;
		// 	shininess = shininess_;
		// }

		// Lambertian(texture *albedo__){
		// 	albedo_ = albedo__;
		// }

		Lambertian(const vec3 &attenuation, vec3 & ambient_, vec3 & specular_, float shininess_){
			albedo = attenuation;
			ambient = ambient_;
			specular = specular_;
			shininess = shininess_;

			albedo_ = new constant_texture(vec3(1, 0, 0)); 
		}

		Lambertian(const vec3 &attenuation, bool textureEnable_){
			albedo = attenuation;
			textureEnable = textureEnable_;

			texture* t1 = new constant_texture(vec3(1, 0, 0)); 
			texture* t2 = new constant_texture(vec3(0, 0, 1)); 
			albedo_ = new checker_texture(t1,t2); 
		}

		vec3 random_in_unit_sphere() const{
			vec3 p;
			do{
				p = 2.0*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
			}while(dot(p,p) >= 1.0);
			return p;
		}
			
		bool scatter(const Ray &r, const HitRecord &ht, vec3 & attenuation, Ray &scattered) const {
			(void) (r);
			vec3 target = ht.origin + ht.normal + random_in_unit_sphere();
			scattered = Ray(ht.origin, target-ht.origin);
			if (textureEnable){
				attenuation = albedo_->value(ht.origin);	
			}else{
				attenuation = albedo;
			}

			// cout << ht.u << ", " << ht.v << ", " << ht.origin << endl;
			
			return true;
		}
};

#endif