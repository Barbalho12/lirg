#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec3.h" // necessário para acessar vec3

using namespace utility; 

class Sphere {

    private:
        point3 center; // the origin of the ray.
        float radius; // The ray's direction.

    public:
        
        //=== Alias
        typedef float real_type;

        //=== Special members
        Sphere(point3 c = point3(0,0,0), float r = 0.0){
            center = c;
            radius = r;
        }

        //=== Access methods
        point3 get_center() const { return center; }

        float get_radius() const { return radius; }
};

#endif
