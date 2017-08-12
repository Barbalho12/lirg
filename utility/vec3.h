#ifndef _VEC3_H_
#define _VEC3_H_

#include <cmath>        // sqrt, fabs
#include <iostream>     // cout, cin, endl
#include <cassert>      // assert()
#include <initializer_list> // initializer_list
#include <algorithm>    // copy
#include <iterator>     // std::begin(), std::end(), std::next()
#include <iomanip>      // setprecision()

namespace utility {
    /*!
     * Represents a 3D vector, that might be used to represent
     * points, directions, vectors, colors, offset
     */

    class vec3{

        public:
            //=== Aliases
            typedef float value_type;
            enum field_t {X = 0, Y = 1, Z = 2, R = 0, G = 1, B = 2};

            //=== Members
            value_type e[3];

            //=== Special members
            vec3(float e0 = 0.f, float e1 = 0.f, float e2 = 0.f){
                e[0] = e0;
                e[1] = e1; 
                e[2] = e2;
            }

            // Copy contructor
            vec3(const vec3 &other){
                e[0] = other.e[X]; 
                e[1] = other.e[Y]; 
                e[2] = other.e[Z];
            }

            // vec3(std::initializer_list< value_type > il_){
            //     assert(il_.size() >= 3) ;
            //     std::copy(il_.begin(), std::next(il_.begin(), 3), std::begin(e));
            // }

            //=== Access operators
            value_type x() const { return e[X]; }
            value_type y() const { return e[Y]; }
            value_type z() const { return e[Z]; }
            value_type r() const { return e[R]; }
            value_type g() const { return e[G]; }
            value_type b() const { return e[B]; }

            // // indexed access operator (rhs)
            // value_type operator[](size_t idx) const { return e[idx]; }
            // // indexed access operator (lhs)
            // value_type& operator[](size_t idx) { return e[idx]; }

            //=== Algebraic operators

            bool operator==(const vec3 & other) const {
                return  fabs(e[X] - other.e[X]) < 0.00001f and
                        fabs(e[Y] - other.e[Y]) < 0.00001f and
                        fabs(e[Z] - other.e[Z]) < 0.00001f    ;
            }

            vec3 & operator=(const vec3 & other){
                e[X] = other.e[X];
                e[Y] = other.e[Y];
                e[Z] = other.e[Z];
                return *this;
            }

            // vec3 & operator=(std::initializer_list< value_type > il_){
            //     assert(il_.size() >= 3) ;
            //     std::copy(il_.begin(), std::next(il_.begin(), 3), std::begin(e));
            //     return *this;
            // }


            // Unary '+'
            const vec3& operator+() const { return *this; }
            
            // Unary '-'
            vec3 operator-() const { return vec3(-e[X], -e[Y], -e[Z]); }

            value_type length() const{
                value_type length = (e[X] * e[X]) + (e[Y] * e[Y]) + (e[Z] * e[Z]);
                return sqrt(length);
            }

            value_type squared_length() const{
                value_type length = (e[X] * e[X]) + (e[Y] * e[Y]) + (e[Z] * e[Z]);
                return length;
            }

            vec3& operator+=(const vec3&);
            vec3& operator-=(const vec3&);
            vec3& operator*=(const vec3&);
            vec3& operator/=(const vec3&);
            vec3& operator*=(const value_type);
            vec3& operator/=(const value_type);
            void make_unit_vector();
            vec3 unit_vector(const vec3 &v);
    };

    typedef vec3 rgb;
    typedef vec3 offset;
    typedef vec3 point3;
} // namespace utility

#include "vec3.cpp"

#endif
