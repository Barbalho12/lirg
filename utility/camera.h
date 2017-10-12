#ifndef _CAM_H_
#define _CAM_H_

#include "vec3.h"

vec3 random_in_unit_disk(){
	vec3 p;
	do {
		p = 2.0*vec3(drand48(),drand48(),0) - vec3(1,1,0);
	}while (dot(p,p) >= 1.0);
	return p;
}

class Camera{
	public:
		point3 lower_left_corner;
		vec3 v_axis;
		vec3 h_axis;
		point3 origin;

		float lens_radius;
		vec3 u, v, w;

		Camera(){
			
		}

		Camera(point3 &llc, vec3 &va, vec3 &ha, point3 &o){
			lower_left_corner = llc;
			v_axis = va;
			h_axis = ha;
			origin = o;
		}

		Camera(point3 lookfrom, vec3 lookat, vec3 vup, float vflow, float aspect, float aperture, float focus_dist){
			lens_radius = aperture / 2;
			float theta = vflow*M_PI/180;
			float half_height = tan(theta/2);
			float half_width = aspect * half_height;
			origin = lookfrom;
			
			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup,w));
			v = cross(w,u);
			
			lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - w*focus_dist;
			h_axis = 2*half_width*focus_dist*u;
			v_axis = 2*half_height*focus_dist*v;

			// std::cout << "Look from = " << lookfrom << "\n";
   //          std::cout << "w = " << w << "\n";
   //          std::cout << "u = " << u << "\n";
   //          std::cout << "v = " << v << "\n";
   //          std::cout << "Half width = " << half_width << "\n";
   //          std::cout << "Half height = " << half_height << "\n";

   //          vec3 llc = lookfrom - (half_width * u) - (half_height * v) - w;
   //          std::cout << "Look from = " << lookfrom << "\n";
   //          std::cout << " = " << (half_width * u) << "\n";
   //          std::cout << " = " << (half_height * v) << "\n";
   //          std::cout << "w = " << w << "\n";

   //          vec3 horizontal = 2 * half_width  * u;
   //          vec3 vertical   = 2 * half_height * v;

   //          std::cout << "llc = " << llc << "\n";
   //          std::cout << "horizontal = " << horizontal << "\n";
   //          std::cout << "vertical = " << vertical << "\n";
		}

		// Camera(point3 lookfrom, vec3 lookat, vec3 vup, float vflow, float aspect){
		// 	vec3 u, v, w;
		// 	float theta = vflow*M_PI/180;
		// 	float half_height = tan(theta/2);
		// 	float half_width = aspect * half_height;
		// 	origin = lookfrom;
		// 	w = unit_vector(lookfrom - lookat);
		// 	u = unit_vector(cross(vup,w));
		// 	v = cross(w,u);


		// 	lower_left_corner = vec3(-half_width, -half_height, -1.0);
		// 	lower_left_corner = origin - half_width*u - half_height*v - w;
		// 	h_axis = 2*half_width*u;
		// 	v_axis = 2*half_height*v;
		// }

		Ray getRay(float s, float t){
			vec3 rd = lens_radius*random_in_unit_disk();
			vec3 offset = u * rd.x() + v * rd.y();
			return Ray(origin + offset, lower_left_corner+s*h_axis + t*v_axis - origin - offset);
		}
};

#endif