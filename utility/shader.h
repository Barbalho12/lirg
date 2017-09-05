#ifndef _SHADE_H_
#define _SHADE_H_

#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "scene.h"

using namespace utility;
using namespace std;


class Shader{

	protected: 
		Scene scene;

	public:

		Shader( Scene &scene_){
			scene = scene_;
		}

		Shader( ){
		}

		//Verifica hit de todos objetos;
		bool hit_anything(HitRecord &ht, const Ray r){
		    HitRecord ht_aux;
		    bool flag = false;
		    for(unsigned int i = 0; i < scene.getObjects().size(); i++){
		        scene.getObject(i)->hit(r, scene.min_depht, scene.max_depht, ht_aux);
		        if(ht_aux.t < ht.t){
		            ht = ht_aux;
		            flag = true;
		        }
		    }
		    return flag;
		}

		virtual rgb color(const Ray &r) = 0;
};

#endif