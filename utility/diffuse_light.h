#ifndef _DIFFUSE_LIGHT_H_
#define _DIFFUSE_LIGHT_H_
#include "material.h"
#include "object.h"
#include "texture.h"

class Diffuse_Light : public Material{
	public:
		texture *emit;

		Diffuse_Light(texture *a){
			emit = a;
		}
			
		bool scatter(const Ray &r, const HitRecord &ht, vec3 & attenuation, Ray &scattered) const {
			return false;
		}

		vec3 emitted(const vec3 &p, float u, float v) const{
			return emit->value(p);
		}
};

#endif