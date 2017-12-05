#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "object.h"
#include "ray.h"
#include "vec3.h"

class Material{

	public:
		virtual bool scatter(const Ray &r, const struct HitRecord &ht, vec3 & attenuation, Ray &scatterd) const = 0;
		virtual vec3 emitted(const vec3 &p, float u = 0.0, float v = 0.0) const{
			return vec3(0,0,0);
		}
};

#endif