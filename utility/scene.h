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
	
};

#endif