#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <iostream>
#include "vec3.h"
#include "ray.h"

using namespace utility;
using namespace std;

class Background{

	private:
		rgb top_left;
		rgb bottom_left;
		rgb top_right;
		rgb bottom_right;

	public:

		Background(){
			top_left = vec3(0,0,0);
			bottom_left = vec3(0,0,0);
			top_right = vec3(0,0,0);
			bottom_right = vec3(0,0,0);
		}

		Background( rgb top_left_, rgb bottom_left_, rgb top_right_, rgb bottom_right_){
			top_left =top_left_/255.99f;
			bottom_left = bottom_left_/255.99f;
			top_right = top_right_/255.99f;
			bottom_right = bottom_right_/255.99f;
		}

		Background( rgb total){
			top_left = total/255.99f;
			bottom_left = total/255.99f;
			top_right = total/255.99f;
			bottom_right = total/255.99f;
		}


		rgb getColor(const Ray &r_){
		    float t = 0.5 * r_.get_direction().y() + 0.5;
		    float u = 0.25 * r_.get_direction().x() + 0.5;

		    rgb result = bottom_left*(1-t)*(1-u) + 
		                 top_left*t*(1-u) + 
		                 bottom_right*u*(1-t) + 
		                 top_right*t*u;

		    return result;
		}

};

#endif