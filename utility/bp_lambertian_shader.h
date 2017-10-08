#ifndef _BP_LAMBERTIAN_SHADER_H_
#define _BP_LAMBERTIAN_SHADER_H_

#include <iostream>
#include "shader.h"

using namespace utility;
using namespace std;

class BP_LambertianShader : public Shader{
	

	public:

		BP_LambertianShader( Scene &scene_) : Shader(scene_){
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


		rgb color_rec(const Ray &r, int depth){
			HitRecord ht;
		    ht.t = scene.max_depht;

		    if(hit_anything(ht, r)){

		    	Ray scattered;
		    	vec3 attenuation;
		    	if(depth < scene.max_depht && ht.material->scatter(r, ht, attenuation, scattered)){


		    		vec3 ks;
					float p;
					vec3 ia;
					vec3 kd;

		    		if (Metal* m = dynamic_cast<Metal*>(ht.material)) {
        				ks = m->specular;
						p = m->shininess;
						ia = m->ambient;
						kd = m->albedo;
   					}else if(Lambertian* l = dynamic_cast<Lambertian*>(ht.material)) {
   						ks = l->specular;
						p = l->shininess;
						ia = l->ambient;
						kd = l->albedo;
   					}

   			// 		if(((int)(100 * ht.origin.x()))%3 == 0){
   			// 			attenuation = rgb(1,0,0);
   			// 		}else if(((int)(100 * ht.origin.x()))%3 == 1){
						// attenuation = rgb(0,1,0);
   			// 		}else{
   			// 			attenuation = rgb(0,0,1);
   			// 		}

					vec3 N = ht.normal;
					vec3 ka = scene.getNaturalLight();

					vector<Light*> lights = scene.getLights();

					rgb c1, c2;

			    	for(unsigned int i = 0; i < lights.size(); i++){

			    		Light *light = scene.getLight(i);

			    		vec3 halfDir = unit_vector(unit_vector(light->direction()) - r.get_direction());
		                float specular = max(0.0, dot(halfDir, ht.normal));
		                specular = pow(specular, p);
			
						Ray shadowRay = Ray(ht.origin, light->direction());
					    HitRecord shadowHT;
					    shadowHT.t = scene.getMaxDepht();
				    	if(!hit_anything(shadowHT, shadowRay)){
				    		c1 += attenuation * color_rec(scattered, depth+1) * max(0.0, dot(unit_vector(light->direction()  - N), ht.normal)) * light->intensity(ht.normal);
				    		c2 += ks * specular * light->intensity(ht.normal);
				    	}
			    	}

			    	rgb c0 = ka*ia;

					return normalize_min_max((c1+c2)+c0);

		    		// return attenuation*color_rec(scattered, depth+1)*;
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