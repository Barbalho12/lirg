#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object.h"
#include "vec3.h"
#include <vector>

using namespace utility;
using namespace std;

class Triangle : public Object {

    private:

        // https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
        //MOLLER_TRUMBORE 
        //https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
        float hit_triangle(Ray r, float t_max){

            vec3 e1 = p1 - p0;
            vec3 e2 = p2 - p0;

            // Calculate planes normal vector
            vec3 pvec = cross(r.get_direction(), e2);
            float det = dot(e1, pvec);

            if (det < 1e-8 && det > -1e-8) {
                return t_max+1;
            }

            float inv_det = 1 / det;
            vec3 tvec = r.get_origin() - p0;
            float u = dot(tvec, pvec) * inv_det;
            if (u < 0 || u > 1) {
                return t_max+1;
            }

            vec3 qvec = cross(tvec, e1);
            float v = dot(r.get_direction(), qvec) * inv_det;
            if (v < 0 || u + v > 1) {
                return t_max+1;
            }
            float t = dot(e2, qvec) * inv_det;
            return t;
        }

    public:

        point3 p0;
        point3 p1;
        point3 p2;


        Triangle(point3 p0_, point3 p1_, point3 p2_, Material *material_){
            p0 = p0_;
            p1 = p1_;
            p2 = p2_;
            material = material_;
        }

        vector<point3*> getPoints(){
            vector<point3*> points;
            points.push_back(&p0);
            points.push_back(&p1);
            points.push_back(&p2);
            return points;
        }

        bool hit(Ray r, float t_min, float t_max, HitRecord &ht){
            ht.t = t_max; 

            float t_aux = hit_triangle(r, t_max);

            if(ht.t > t_aux && t_aux > t_min){
                ht.t = t_aux;
                ht.origin = - r.point_at(t_aux);
               
                // ht.normal = unit_vector((p0 - p1)*(p0 - p2)); //MODE 1
                // ht.normal = unit_vector(-r.point_at(t_aux));  //MODE 2
                ht.normal = unit_vector(cross((p0 - p1),(p0 - p2))); //MODE 1

                ht.material = material;
                return true;
            }
            return false;
        }
};

#endif
