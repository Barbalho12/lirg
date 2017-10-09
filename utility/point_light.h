#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"
#include "vec3.h"

using namespace utility;

class PointLight : public Light{

	public:

     PointLight(vec3 o = vec3(-2,1,-1), rgb i = rgb(1,1,1)) : Light(i, o){
     }

     rgb intensity(point3 p){
          return m_intensity;
     }

     vec3 origin(){
          return m_direction;
     }

     vec3 direction(point3 p){
          return (m_direction - p);
     }

    //virtual ~PointLight() { };
};

#endif