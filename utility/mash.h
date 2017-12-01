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
            for(unsigned int i = 0; i < mash.size(); i++){
                points.push_back(mash[i]->getPoints()[0]);
                points.push_back(mash[i]->getPoints()[1]);
                points.push_back(mash[i]->getPoints()[2]);
            }
        }

        void resizeSphere(){
            float x_max =-100000;
            float x_min =100000;
            float y_max =-100000;
            float y_min =100000;
            float z_max =-100000;
            float z_min =100000;

            for(int i = 0; i < points.size(); i++){
                if(points[i]->x() > x_max){
                    x_max = points[i]->x();
                }
                if(points[i]->y() > y_max){
                    y_max = points[i]->y();
                }
                if(points[i]->z() > z_max){
                    z_max = points[i]->z();
                }
                if(points[i]->x() < x_min){
                    x_min = points[i]->x();
                }
                if(points[i]->y() < y_min){
                    y_min = points[i]->y();
                }
                if(points[i]->z() < z_min){
                    z_min = points[i]->z();
                }
            }

            //centro da esfera
            point3 center = point3((x_max+x_min)/2, (y_max+y_min)/2, (z_max+z_min)/2);

            //raio
            float radius = sqrt( pow(x_max - x_min, 2) + pow(y_max-y_min, 2) + pow(z_max-z_min, 2))/2;

            sphere = new Sphere(center, radius);
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
