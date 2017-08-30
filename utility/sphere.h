#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "object.h"
#include "vec3.h"

using namespace utility; 

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

        point3 get_center() const { return center; }
        float get_radius() const { return radius; }
        bool hit(Ray r, float t_min, float t_max, HitRecord &ht){
            ht.t = t_max; 
            ht.origin = center;

            float t_aux = hit_sphere(r);

            if(ht.t > t_aux && t_aux > t_min){
                ht.t = t_aux;
                ht.origin = r.point_at(t_aux);
                ht.normal = (ht.origin - center) / radius;
                return true;
            }
            return false;
        }
};

#endif
