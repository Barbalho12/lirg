#ifndef _OBJ_H_
#define _OBJ_H_

class Object {
	
	vec3 origin;
	Material material;
	bool hit(Ray r, float t_min, float t_max, HitRecord &ht);
};

#endif