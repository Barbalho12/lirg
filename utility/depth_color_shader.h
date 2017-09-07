#ifndef _DEPTHCOLOR_SHADER_H_
#define _DEPTHCOLOR_SHADER_H_

#include <iostream>
#include "shader.h"

using namespace utility;
using namespace std;

class DepthColorShader : public Shader{

	private:
		rgb depth_foreground;
		rgb depth_background;

	public:

		DepthColorShader( Scene &scene_, rgb d_fore, rgb d_back) : Shader(scene_){
			depth_foreground = d_fore;
			depth_background = d_back;
		}

		rgb color(const Ray &r){
			HitRecord ht;
		    ht.t = scene.max_depht;

		    if(hit_anything(ht, r)){

		    	ht.t = ht.t/scene.max_depht;
		        return ((1-ht.t) * depth_foreground) + (ht.t*depth_background);

		    }else{
		    	return depth_background;
		    }
		   
		}

};

#endif