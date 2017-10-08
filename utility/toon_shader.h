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

		rgb color(const Ray &r){
			HitRecord ht;
		    ht.t = scene.getMaxDepht();

		    if(hit_anything(ht, r)){
		    	Toon *toon = dynamic_cast<Toon*>(ht.material);
		    	// float hitAngle = fabs(dot(ht.normal, r.get_direction()));
		    	//printf("%lf\n", hitAngle);

		    	float angle = dot(ht.normal, r.get_direction())/(ht.normal.length()*r.get_direction().length());
			    float piangle = acos(angle) * 180.0 / PI;
			    
			    piangle = ((int) piangle) % 90;
			    int factor = 90/toon->colors.size();

			    if(piangle < 10){
			    	return rgb(0, 0, 0);
			    }

			    for(unsigned int i = 0; i < toon->colors.size(); i++){
			    	if(piangle >= i*factor && piangle < (i*factor+factor)){
			    		return rgb(toon->colors[i]);
			    	}


			    }

			    return rgb(1, 1, 1);

			    // piangle = ((int) piangle) % 90; 
			    // if(piangle > 0 && piangle <= 30){
			    // 	return rgb(0, 0, 1);
			    // }else if(piangle > 30 && piangle <= 60){
			    // 	return rgb(1, 0, 0);
			    // }else if(piangle > 60 && piangle <= 90){
			    // 	return rgb(1, 1, 1);
			    // }else{
			    	// return rgb(1, 1, 1);
			    // }
		    	

		    	// if(hitAngle < 0.3){

		    	// 	return rgb(0, 0, 0);
		    	// }
		    	// 	return rgb(1, 1, 1);


		    	

		    	
		  //   	vec3 ks = lambertian->specular;
				// float p = lambertian->shininess;
				// vec3 ia = lambertian->ambient;
				// vec3 kd = lambertian->albedo;
				// vec3 N = ht.normal;
				// vec3 ka = scene.getNaturalLight();

				// vector<DirectionLight*> lights = scene.getLights();

				// rgb c1, c2;

		  //   	for(unsigned int i = 0; i < lights.size(); i++){

		  //   		DirectionLight *light = scene.getLight(i);

		  //   		vec3 halfDir = unit_vector(unit_vector(light->direction()) - r.get_direction());
	   //              float specular = max(0.0, dot(halfDir, ht.normal));
	   //              specular = pow(specular, p);
		
				//     Ray shadowRay = Ray(ht.origin, light->direction());
				//     HitRecord shadowHT;
				//     shadowHT.t = scene.getMaxDepht();
			 //    	if(!hit_anything(shadowHT, shadowRay)){
			 //    		c1 += (kd * max(0.0, dot(unit_vector(light->direction()  - N), ht.normal))) * light->intensity();
			    		
			 //    	}
			 //    	c2 += ks * specular * light->intensity();
		  //   	}

		  //   	rgb c0 = ka*ia;

				// return normalize_min_max((c1+c2)+c0);

		    }else{
				return scene.background.getColor(r);
		    }
		}
};

#endif