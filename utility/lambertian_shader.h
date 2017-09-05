#ifndef _LAMBERTIAN_SHADER_H_
#define _LAMBERTIAN_SHADER_H_

#include <iostream>
#include "shader.h"

using namespace utility;
using namespace std;

class LambertianShader : public Shader{
	
	private:
		Header header;

	public:

		LambertianShader( Scene &scene_, Header header_) : Shader(scene_){
			header = header_;
		}


		rgb color_rec(const Ray &r, int depth){
			HitRecord ht;
		    ht.t = scene.max_depht;

		    if(hit_anything(ht, r)){

		    	Ray scattered;
		    	vec3 attenuation;
		    	if(depth < scene.max_depht && ht.material->scatter(r, ht, attenuation, scattered)){
		    		return attenuation*color_rec(scattered, depth+1);
		    	}else{
		    		return rgb(0,0,0);
		    	}
		    }else{
		    	return make_background_point(r);
		    }

		}

		rgb color(const Ray &r){
			return color_rec(r, 0);
		}

		rgb make_background_point(const Ray &r_){
		    rgb top_left = header.upper_left/255.99f;
		    rgb bottom_left = header.lower_left/255.99f;
		    rgb top_right = header.upper_right/255.99f;
		    rgb bottom_right = header.lower_right/255.99f;

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