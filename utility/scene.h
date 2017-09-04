#ifndef _SCENE_H_
#define _SCENE_H_

#include "../utility/vec3.h"
#include "object.h"
#include "sphere.h"
#include "image.h"
#include <vector>

using namespace std;

class Scene{
	private:
		vector<Object*> objects;
		//Object background;
		
	public:
		float min_depht;
		float max_depht;

		Scene(){}

		// Scene(Object o){
		// 	background = o;
		// }

		void addObject(Object * o){
			objects.push_back(o);
		}

		void setObjects(vector<Object*> objects_){
			objects = objects_;
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