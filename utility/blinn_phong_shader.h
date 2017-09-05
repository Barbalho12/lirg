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

	public:

		BlinnPhongShader( Scene &scene_) : Shader(scene_){

		}

		rgb color(const Ray &r){
			rgb intensity = rgb(1,1,1);
			vec3 direction = vec3(20,10,5);

			HitRecord ht;
		    ht.t = scene.getMaxDepht();

		    if(hit_anything(ht, r)){
				Lambertian *kd = dynamic_cast<Lambertian*>(ht.material);
				return rgb(0,0,0);	
		    }

			//https://en.wikipedia.org/wiki/Blinn%96Phong_shading_model#Fragment_shader
			return rgb(1,1,1);
		} 

};

#endif