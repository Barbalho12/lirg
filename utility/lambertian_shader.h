#ifndef _LAMBERTIAN_SHADER_H_
#define _LAMBERTIAN_SHADER_H_

#include <iostream>
#include "shader.h"

using namespace utility;
using namespace std;

class LambertianShader : public Shader{


	public:

		LambertianShader( Scene &scene_) : Shader(scene_){

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
		    		return vec3(0,0,0);
		    	}
		    }else{
		    	return vec3(0.5,0.5,0.5);
		    }

		}

		rgb color(const Ray &r){
			return color_rec(r, 0);
		}

};

#endif