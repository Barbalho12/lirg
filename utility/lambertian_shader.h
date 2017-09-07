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
		    	return scene.background.getColor(r);
		    }

		}

		rgb color(const Ray &r){
			return color_rec(r, 0);
		}

};

#endif