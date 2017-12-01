#ifndef _TEXTURE_H_
#define _TEXTURE_H_ 

#include <iostream>
#include "vec3.h"
#include "ray.h"
#include <cmath> 

using namespace utility;
using namespace std;


class texture  {
    public:
        virtual vec3 value(const vec3& p, float u=0, float v=0) const = 0;
};

class constant_texture : public texture {
    
    public:
        constant_texture(vec3 c) { 
        	color = c;
        }
        virtual vec3 value( const vec3& p, float u, float v) const {
            return color;
        }
        vec3 color;
};

class checker_texture : public texture {
    public:
    	texture *odd;
        texture *even;
        checker_texture() { 
        	odd = nullptr; 
        	even = nullptr;
        }
        checker_texture(texture *t0, texture *t1){ 
        	even = t0;
        	odd = t1;
        }
        virtual vec3 value(const vec3& p, float u, float v) const {
            float sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
            if (sines < 0){
                return odd->value(p, u, v);
            }else{
                return even->value(p, u, v);
            }
        }
};



#endif