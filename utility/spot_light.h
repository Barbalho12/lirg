#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <cmath>
#include "light.h"
#include "vec3.h"

using namespace utility;
using namespace std;

class SpotLight : public Light{

	public:
          vec3 origin;
          float openAngle;

     SpotLight(rgb i = vec3(1,1,1), vec3 o = vec3(0,0,0), vec3 d = vec3(1,1,1), float a = 0.03490659) : Light(i, d){
          origin = o;
          openAngle = a;
     }

     rgb intensity(point3 p){
          return m_intensity;
     }

     vec3 direction(point3 p){
          vec3 dir = origin - p;
          float angle = dot(-m_direction, dir) / (-m_direction.length() * dir.length());
          if (angle > openAngle) {
               return dir;
          }
          return vec3(0, 0, 0);
     }

    //virtual ~SpotLight() { };
};

#endif