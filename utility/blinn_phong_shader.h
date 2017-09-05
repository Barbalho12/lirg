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

//		   * ambiente: (0.1,0.1,0.1)
//         * difuso: (0.0,0.3,0.8)
//         * specular: (0.9,0.9,0/9)
//         * expoente especular: 64 (variando para cada imagem)

		// + intensidade (1,1,1)
		// + direção (20,10,5)
	private:
		Header header;

	public:

		BlinnPhongShader( Scene &scene_, Header header_) : Shader(scene_){
			header = header_;
		}

		rgb color(const Ray &r){
			DirectionLight light(rgb(1,1,1), vec3(20,10,5)); // Ler de arquivo e armazenar em Light
			// rgb intensity = rgb(1,1,1); // Ler de arquivo e armazenar em Light
			// vec3 direction = vec3(20,10,5); // Ler de arquivo e armazenar em Light

			HitRecord ht;
		    ht.t = scene.getMaxDepht();

		    if(hit_anything(ht, r)){
				Lambertian *kd = dynamic_cast<Lambertian*>(ht.material);
				//vec3 lightDir = unit_vector(light.direction() - ht.normal);
				rgb c = (kd->albedo * dot(unit_vector(light.direction() - ht.normal), ht.normal)) * light.intensity();
				//rgb posLightIntensity = c * intensity;
				return c;
		    }else{
				return make_background_point(r);
		    }

			//https://en.wikipedia.org/wiki/Blinn%96Phong_shading_model#Fragment_shader
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