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

	private:
		Header header;

	public:

		BlinnPhongShader( Scene &scene_, Header header_) : Shader(scene_){
			header = header_;
		}

		float max(float a, float b){
			if(a>b){
				return a;
			}
			return b;
		}

		rgb normalize_min_max(rgb c){
			if(c.r() > 1.f){
				c.e[0] = 1.0;
			}
			if(c.g() > 1.f){
				c.e[1] = 1.0;
			}
			if(c.b() > 1.f){
				c.e[2] = 1.0;
			}
			if(c.r() < 0.f){
				c.e[0] = 0.0;
			}
			if(c.g() < 0.f){
				c.e[1] = 0.0;
			}
			if(c.b() < 0.f){
				c.e[2] = 0.0;
			}
			return c;
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

				vector<DirectionLight*> lights = scene.getLights();

				rgb c1, c2;

		    	for(unsigned int i = 0; i < lights.size(); i++){

		    		DirectionLight *light = scene.getLight(i);

		    		vec3 halfDir = unit_vector(unit_vector(light->direction()) - r.get_direction());
	                float specular = max(0.0, dot(halfDir, ht.normal));
	                specular = pow(specular, p);
		
					c1 += (kd * dot(unit_vector(light->direction()  - N), ht.normal)) * light->intensity();
				    c2 += ks * specular * light->intensity(); 

		    	}

		    	rgb c0 = ka*ia;

				return normalize_min_max(c0+c1+c2);

		    }else{
				return make_background_point(r);
		    }
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