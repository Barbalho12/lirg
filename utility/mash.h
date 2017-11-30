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

        vector<point3*> points;


        Mash(vector<Triangle*> mash_, Sphere* sphere_){
            mash = mash_;
            sphere = sphere_;

            setPoints();
        }

        void setPoints(){
            vector<point3*> points;

            points.push_back(sphere->getPoints()[0]);

            for(unsigned int i = 0; i < mash.size(); i++){
                points.push_back(mash[i]->getPoints()[0]);
                points.push_back(mash[i]->getPoints()[1]);
                points.push_back(mash[i]->getPoints()[2]);
            }
            cout << "ok" << endl;
        }

        vector<point3*> getPoints(){
            return points;
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
