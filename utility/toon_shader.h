#ifndef _TOON_SHADER_H_
#define _TOON_SHADER_H_

#define PI 3.14159265

#include "shader.h"
#include "light.h"
#include "toon.h"
#include <stdio.h>

using namespace utility;
using namespace std;

class ToonShader : public Shader{
	public:
		ToonShader( Scene &scene_) : Shader(scene_){
		}


		float getAngle(vec3 v1, vec3 v2){
			//resultado da expressão [[[   cos phi = v1*v2 / |v1| * |v2|    ]]]
		    //Retorna cos phi
			float angle = dot(v1, v2)/(v1.length()*v2.length());

			//Anglo em graus entre v1 e v2
			float piangle = acos(angle) * 180.0 / PI;

			//Gambiarra para variar entre 0° e 90° (Não acho que esteja correto, fiz pra testar)
			piangle = ((int) piangle) % 90;

			return piangle;
		}

		float max(float a, float b){
			if(a>b){
				return a;
			}
			return b;
		}

		rgb color(const Ray &r){
			HitRecord ht;
		    ht.t = scene.getMaxDepht();

		    if(hit_anything(ht, r)){
		    	Toon *toon = dynamic_cast<Toon*>(ht.material);

		    	//Anglo entre o raio da camera e anormal do ponto
			    float angleHitCamera = getAngle(ht.normal, r.get_direction());
			    
			    //Margem da borda 
			    if(angleHitCamera < 10){
			    	return toon->borderColor;
			    }else{

			    	//Factor de variação 90 dividido pelo numero de cores (depende do valor maximo de 'piangle', que no caso da gambiarra é 90°)
			    	float factor = 90.0/toon->colors.size();

			    	// vec3 ks = lambertian->specular;
					// float p = lambertian->shininess;
					vec3 ia = vec3(0.1, 0.1, 0.1);
					rgb kd;
					vec3 N = ht.normal;
					vec3 ka = scene.getNaturalLight();

				    	
			    	vector<Light*> lights = scene.getLights();

					rgb c1, c2;

			    	for(unsigned int i = 0; i < lights.size(); i++){

			    		Light *light = scene.getLight(i);

			    		//Anglo entre a luz e anormal do ponto
			    		float angleHitLight = getAngle(light->direction(), ht.normal);

						//Percorre cada cor
					    for(unsigned int color_toon = 0; color_toon < toon->colors.size(); color_toon++){
				    		
				    		//Se o anglo estiver na margem  [[ (i*factor)  =<   piangle   < (i*factor+factor) ]] colore
					    	if(angleHitLight >= color_toon*factor && angleHitLight < (color_toon*factor+factor)){
					    		kd =  toon->colors[color_toon];
					    	}
					    }	

			    		//vec3 halfDir = unit_vector(unit_vector(light->direction()) - r.get_direction());
		                // float specular = max(0.0, dot(halfDir, ht.normal));
		                // specular = pow(specular, p);
			
					    Ray shadowRay = Ray(ht.origin, light->direction());
					    HitRecord shadowHT;
					    shadowHT.t = scene.getMaxDepht();
				    	
				    	if(!hit_anything(shadowHT, shadowRay)){
				    		c1 += (kd * max(0.0, dot(unit_vector(light->direction()  - N), ht.normal))) * light->intensity(ht.normal);
				    		
				    	}
					    	// c2 += ks * specular * light->intensity();
				    }

			    	rgb c0 = ka*ia;

					return normalize_min_max(c1+c0);
				}
		    }else{
				return scene.background.getColor(r);
		    }
		}
};

#endif