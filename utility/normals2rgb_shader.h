#ifndef _NORMALS2RGB_SHADER_H_
#define _NORMALS2RGB_SHADER_H_

#include <iostream>
#include "shader.h"

using namespace utility;
using namespace std;

class Normals2RGBShader	 : public Shader{

	public:

		Normals2RGBShader( Scene &scene_) : Shader(scene_){
		}

		rgb color(const Ray &r){
			HitRecord ht;
		    ht.t = scene.getMaxDepht();

		    if(hit_anything(ht, r)){
		    	return rgb((ht.normal.x()+1.0)/2.0,
		                   (ht.normal.y()+1.0)/2.0,
		                   (ht.normal.z()+1.0)/2.0);
		    }else{
		    	return scene.background.getColor(r);
		    }
		    
		}

};

#endif