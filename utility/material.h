#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "object.h"
#include "ray.h"
#include "vec3.h"

class Material{

	public:
		virtual bool scatter(const Ray &r, const struct HitRecord &ht, vec3 & attenuation, Ray &scatterd) const = 0;
};

#endif