#ifndef _MASH_H_
#define _MASH_H_

#include "object.h"
#include "vec3.h"
#include "triangle.h"
#include <vector>
#include "sphere.h"

using namespace utility;
using namespace std;

class Mash : public Object {

    public:

        vector<Triangle*> mash;
        Sphere* sphere;


        Mash(vector<Triangle*> mash_, Sphere* sphere_){
            mash = mash_;
            sphere = sphere_;
        }

        vector<point3*> getPoints(){
            return sphere->getPoints();
        }

        bool hit(Ray r, float t_min, float t_max, HitRecord &ht){
            bool result = false;
            if(sphere->hit(r, t_min, t_max, ht)){
                for (unsigned int i = 0; i < mash.size(); i++){
                    result =  mash[i]->hit(r, t_min, t_max, ht);
                    if(result){
                        break;
                    }
                }
            }
            return result;
        }
};

#endif
