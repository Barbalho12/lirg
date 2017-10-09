#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

using namespace utility;

class Light{
	protected:
		rgb m_intensity; 
		vec3 m_direction; 

     public:
          Light(rgb i, vec3 d){
               m_intensity = i;
               m_direction = d;
          }
          
          virtual rgb intensity(point3 p) = 0;
          virtual vec3 direction(point3 p) = 0;
};

#endif