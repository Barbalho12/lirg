#ifndef _BLINNPHONG_SHADER_H_
#define _BLINNPHONG_SHADER_H_

#include <iostream>
#include "shader.h"
#include <math.h>
#include "light.h"

using namespace utility;
using namespace std;

class BlinnPhongShader : public Shader{


	public:

		BlinnPhongShader( Scene &scene_) : Shader(scene_){

		}

		rgb color(const Ray &r){

			//https://en.wikipedia.org/wiki/Blinn%96Phong_shading_model#Fragment_shader
			return rgb(0,0,0);
		} 

};

#endif