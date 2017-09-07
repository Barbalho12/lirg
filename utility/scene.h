#ifndef _SCENE_H_
#define _SCENE_H_

#include "../utility/vec3.h"
#include "object.h"
#include "sphere.h"
#include "image.h"
#include "light.h"
#include "background.h"
#include <vector>

using namespace std;

class Scene{
	private:
		vector<Object*> objects;
		vector<DirectionLight*> lights;
		rgb natural_light;
		
	public:
		Background background;

		float min_depht;
		float max_depht;

		Scene(){}


		void addObject(Object * o){
			objects.push_back(o);
		}

		void setObjects(vector<Object*> objects_){
			objects = objects_;
		}

		void setLights(vector<DirectionLight*> lights_){
			lights = lights_;
		}

		vector<DirectionLight*> getLights(){
			return lights;
		}

		DirectionLight* getLight(int i){
			return lights[i];
		}

		vector<Object*> getObjects(){
			return objects;
		}

		Object* getObject(int i){
			return objects[i];
		}

		void setMaxDepht(int max_depht_){
			max_depht = max_depht_;
		}

		void setNaturalLight(rgb natural_light_){
			natural_light = natural_light_;
		}

		rgb getNaturalLight(){
			return natural_light;
		}

		void setMinDepht(int min_depht_){
			min_depht = min_depht_;
		}

		float getMaxDepht(){
			return max_depht;
		}

		float getMinDepht(){
			return min_depht;
		}
	
};

#endif