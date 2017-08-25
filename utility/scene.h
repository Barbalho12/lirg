#ifndef _SCENE_H_
#define _SCENE_H_

#include "../utility/vec3.h"
#include "object.h"
#include "image.h"
#include <vector>

using namespace std;

// typedef struct RGB{
// 	unsigned char r;
// 	unsigned char g;
// 	unsigned char b;
// };

class Scene{

	vector<Object> objects;
	Image background; // Object

	Scene(Image b){
		background = b;
	}

	void addObject(Object o){
		objects.push_back(o);
	}
	
};

#endif