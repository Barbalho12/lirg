#ifndef _SCENE_H_
#define _SCENE_H_

#include "../utility/vec3.h"
#include "object.h"
#include "image.h"
#include <vector>

using namespace std;

class Scene{

	vector<Object> objects;
	Object background;

	Scene(Object o){
		background = o;
	}

	void addObject(Object o){
		objects.push_back(o);
	}
	
};

#endif