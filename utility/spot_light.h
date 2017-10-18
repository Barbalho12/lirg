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

		SpotLight(rgb i = vec3(1,1,1), vec3 o = vec3(0,0,0), vec3 d = vec3(1,1,1), float a = 90) : Light(i, d){
			origin = o;
			openAngle = a;
		}

		rgb intensity(point3 p){
			vec3 dir = p - origin;
			float angle = (180/3.14) * acos(dot(m_direction, dir) / (m_direction.length() * dir.length()));
			//printf("%lf\n", angle);
			if (angle < openAngle) {
				return m_intensity; // (1 - ((angle - openAngle)));
				//return dir;
			}
			return rgb(0, 0, 0);
			//return m_intensity;
		}

		vec3 direction(point3 p){
			return origin;
		}

    //virtual ~SpotLight() { };
};

#endif