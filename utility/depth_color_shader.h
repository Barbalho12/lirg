#ifndef _RAY_DEPTHCOLORSHADER_H_
#define _RAY_DEPTHCOLORSHADER_H_

#include <iostream>
#include "shader.h"

using namespace utility;
using namespace std;

class DepthColorShader : public Shader{


	public:

		DepthColorShader( Scene &scene_) : Shader(scene_){

		}

		rgb color(const Ray &r){
			HitRecord ht;
		    ht.t = scene.max_depht;
		    hit_anything(ht, r);
		    return make_foreground_to_background_depth(ht, scene.min_depht, scene.max_depht);
		}

		rgb make_foreground_to_background_depth(HitRecord ht, float min_depht, float max_depht){
		    rgb depth_foreground = rgb(0, 0, 0);
		    rgb depth_background = rgb(1, 1, 1);

		    rgb cor;

		    if (ht.t >= min_depht && ht.t <= max_depht) {
		        ht.t = ht.t/max_depht;
		        cor = ((1-ht.t) * depth_foreground) + (ht.t*depth_background);
		    }else{
		        cor = depth_background;
		    }
		    return cor;
		}

};

#endif