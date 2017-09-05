#ifndef _NORMALS2RGB_SHADER_H_
#define _NORMALS2RGB_SHADER_H_

#include <iostream>
#include "shader.h"

using namespace utility;
using namespace std;

class Normals2RGBShader	 : public Shader{

	private:
		Header header;

	public:

		Normals2RGBShader( Scene &scene_,Header header_ ) : Shader(scene_){
			header = header_;
		}

		rgb color(const Ray &r){
			HitRecord ht;
		    ht.t = scene.getMaxDepht();

		    hit_anything(ht, r);
	
		    return make_background_default(r, ht);
		    
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

		rgb make_background_default(const Ray &r_, HitRecord &ht){
		    if( ht.t >= scene.getMinDepht() && ht.t < scene.getMaxDepht()){
		        return rgb((ht.normal.x()+1.0)/2.0,
		                   (ht.normal.y()+1.0)/2.0,
		                   (ht.normal.z()+1.0)/2.0);
		    }else{
		        return make_background_point(r_);
		    }
		}



};

#endif