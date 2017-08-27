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
		vector<Sphere> objects;
		//Object background;

	public:
		Scene(){}

		// Scene(Object o){
		// 	background = o;
		// }

		void addObject(Sphere o){
			objects.push_back(o);
		}

		vector<Sphere> getObjects(){
			return objects;
		}
	
};

#endif