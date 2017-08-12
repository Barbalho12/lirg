#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h" // necessário para acessar vec3

using namespace utility; 

class Ray {

    private:
        point3 O; // the origin of the ray.
        vec3 D; // The ray's direction.

    public:
        
        //=== Alias
        typedef float real_type;

        //=== Special members
        Ray(point3 o = point3(), vec3 d = vec3()){
            O = o;
            D = d;
        } 

        //=== Access methods
        vec3 get_direction() const { return D; }

        point3 get_origin() const { return O; }

        point3 point_at(real_type t)  const {
            return O + t * D; // parametric equation of the ray.
        }
};

#endif
