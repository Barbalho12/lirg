#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "object.h"
#include "vec3.h"
#include <vector>

using namespace utility;
using namespace std;

class Sphere : public Object {

    private:
        float radius;

        float hit_sphere(Ray r){
            float a = dot(r.get_direction(), r.get_direction());
            float b = dot(((r.get_origin() - center)), r.get_direction());
            float c = dot(((r.get_origin() - center)), ((r.get_origin() - center))) - (radius * radius);  
            float t = (-b - sqrt(dot(b, b) - (dot(a,c))))/a;
            return t;
        }

    public:

        Sphere(point3 c, float r, Material *material_){
            center = c;
            radius = r;
            material = material_;
        }

        Sphere(point3 c, float r){
            center = c;
            radius = r;
        }

        point3 get_center() const { return center; }
        float get_radius() const { return radius; }
        
        void set_radius(float r){
            radius = r;
        }

        vector<point3*> getPoints(){
            vector<point3*> points;
            points.push_back(&center);
            return points;
        }
        
        bool hit(Ray r, float t_min, float t_max, HitRecord &ht){
            ht.t = t_max; 
            ht.origin = center;

            float t_aux = hit_sphere(r);

            if(ht.t > t_aux && t_aux > t_min){
                ht.t = t_aux;
                ht.origin = r.point_at(t_aux);
                ht.normal = (ht.origin - center) / radius;
                ht.material = material;
                return true;
            }
            return false;
        }
};

#endif
