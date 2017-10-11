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

		Camera(point3 lookfrom, vec3 lookat, vec3 vup, float vflow, float aspect){
			vec3 u, v, w;
			float theta = vflow*M_PI/180;
			float half_height = tan(theta/2);
			float half_width = aspect * half_height;
			origin = lookfrom;
			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup,w));
			v = cross(w,u);


			lower_left_corner = vec3(-half_width, -half_height, -1.0);
			lower_left_corner = origin - half_width*u - half_height*v - w;
			// v_axis = origin - half_width*u - half_height*v - w;
			h_axis = 2*half_width*u;
			v_axis = 2*half_height*v;
		}
};

#endif