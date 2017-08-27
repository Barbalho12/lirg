#ifndef _CAM_H_
#define _CAM_H_

#include "vec3.h"

class Camera{
	public:
		point3 lower_left_corner;
		vec3 v_axis;
		vec3 h_axis;
		point3 origin;

		Camera(){
			
		}

		Camera(point3 &llc, vec3 &va, vec3 &ha, point3 &o){
			lower_left_corner = llc;
			v_axis = va;
			h_axis = ha;
			origin = o;
		}
};

#endif