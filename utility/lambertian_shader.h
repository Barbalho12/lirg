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

		float max(float a, float b){
			if(a>b){
				return a;
			}
			return b;
		}

		rgb color_rec(const Ray &r, int depth){
			HitRecord ht;
		    ht.t = scene.max_depht;
		    vector<DirectionLight*> lights = scene.getLights();

		    if(hit_anything(ht, r)){
		    	rgb c1;

		    	for(unsigned int i = 0; i < lights.size(); i++){

		    		DirectionLight *light = scene.getLight(i);
		
				    Ray shadowRay = Ray(ht.origin, light->direction());
				    HitRecord shadowHT;
				    shadowHT.t = scene.getMaxDepht();
			    	if(!hit_anything(shadowHT, shadowRay)){
			    		c1 += (max(0.0, dot(unit_vector(light->direction()  - ht.normal), ht.normal))) * light->intensity();
			    	}
		    	}

		    	Ray scattered;
		    	vec3 attenuation;
		    	if(depth < scene.max_depht && ht.material->scatter(r, ht, attenuation, scattered)){
		    		return attenuation*color_rec(scattered, depth+1)*c1;
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