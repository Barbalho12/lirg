#ifndef _TOON_H_
#define _TOON_H_

#include "material.h"
#include "object.h"
#include "vec3.h"

using namespace std;

class Toon : public Material{
	private:
		
		
		rgb borderColor;
		rgb shadowColor;

	public:
		// vector<float> angles;
		vector<rgb> colors;

		Toon(rgb bc = rgb(0,0,0), rgb sc = rgb(0.4,0.4,0.4)){
			borderColor = bc;
			shadowColor = sc;
		}

		Toon(vector<rgb> c, /*vector<float> a,*/ rgb bc = rgb(0,0,0), rgb sc = rgb(0.4,0.4,0.4)){
			colors = c;
			// angles = a;
			borderColor = bc;
			shadowColor = sc;
		}



		void addGradientColor(rgb color){
			colors.push_back(color);
		}

		bool scatter(const Ray &r, const HitRecord &ht, vec3 & attenuation, Ray &scattered) const {
			return true;
		}
};

#endif