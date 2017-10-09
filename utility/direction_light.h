#ifndef DIRECTION_LIGHT_H
#define DIRECTION_LIGHT_H

#include "light.h"

class DirectionLight : public Light {
	public:
		DirectionLight(rgb i = vec3(0,0,0), vec3 d = vec3(0,0,0)) : Light(i, d){
		}
		
		rgb intensity(point3 p){ 
			return m_intensity;
		}

		vec3 direction(point3 p){
			return m_direction; 
		}

    	virtual ~DirectionLight() { };
};

#endif