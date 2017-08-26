#ifndef _OBJ_H_
#define _OBJ_H_

#include "material.h"
#include "vec3.h"
#include "ray.h"

struct HitRecord{
	float t;
	vec3 origin;
};

class Object {

	protected:
		point3 center;
		Material material;

	public:
		virtual bool hit(Ray r, float t_min, float t_max, HitRecord &ht) = 0;
};

#endif