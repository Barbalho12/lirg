#ifndef _BLINNPHONG_SHADER_H_
#define _BLINNPHONG_SHADER_H_

#include <iostream>
#include "shader.h"
#include <math.h>
#include "light.h"
#include "lambertian.h"


using namespace utility;
using namespace std;

class BlinnPhongShader : public Shader{

	public:

		BlinnPhongShader( Scene &scene_) : Shader(scene_){
		}

		float max(float a, float b){
			if(a>b){
				return a;
			}
			return b;
		}

		//https://en.wikipedia.org/wiki/Blinn%96Phong_shading_model#Fragment_shader
		//https://selan.bitbucket.io/srt/classrt_1_1_blinn_phong_shader.html
		rgb color(const Ray &r){

			HitRecord ht;
		    ht.t = scene.getMaxDepht();

		    if(hit_anything(ht, r)){
		    	Lambertian *lambertian = dynamic_cast<Lambertian*>(ht.material);
		    	
		    	vec3 ks = lambertian->specular;
				float p = lambertian->shininess;
				vec3 ia = lambertian->ambient;
				vec3 kd = lambertian->albedo;
				vec3 N = ht.normal;
				vec3 ka = scene.getNaturalLight();

				vector<Light*> lights = scene.getLights();

				rgb c1, c2;

		    	for(unsigned int i = 0; i < lights.size(); i++){

		    		Light *light = scene.getLight(i);

		    		vec3 halfDir = unit_vector(unit_vector(light->direction(ht.origin)) - r.get_direction());
	                float specular = max(0.0, dot(halfDir, ht.normal));
	                specular = pow(specular, p);
		
				    Ray shadowRay = Ray(ht.origin, light->direction(ht.origin));
				    HitRecord shadowHT;
				    shadowHT.t = scene.getMaxDepht();
			    	if(!hit_anything(shadowHT, shadowRay)){
			    		c1 += (kd * max(0.0, dot(unit_vector(light->direction(ht.origin)  - N), ht.normal))) * light->intensity(ht.origin);
			    		
			    	}
			    	c2 += ks * specular * light->intensity(ht.origin);
		    	}

		    	rgb c0 = ka*ia;

				return normalize_min_max((c1+c2)+c0);

		    }else{
				return scene.background.getColor(r);
		    }
		}

};

#endif