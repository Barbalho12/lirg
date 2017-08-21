#ifndef _CAM_H_
#define _CAM_H_

#include "vec3.h"

class Camera{
	public:
		point3 lower_left_corner;
		vec3 vertical_axis;
		vec3 horizontal_axis;
		point3 origin;

		Camera(const point3 &llc, const vec3 &va, const vec3 &ha, const point3 &o){
			lower_left_corner = llc;
			vertical_axis - va;
			horizontal_axis = ha;
			origin = o;
		}
};

#endif