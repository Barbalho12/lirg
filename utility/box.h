#ifndef _BOX_H_
#define _BOX_H_

#include "object.h"
#include "vec3.h"
#include "triangle.h"
#include <vector>

using namespace utility;
using namespace std;

class Box : public Object {

    private:

    public:

        vector<point3> vertices;
        vector<Triangle*> triangles;


        Box(point3 p0, point3 p7, Material *material_){

            point3 p1 = point3(p7.x(), p0.y(), p0.z());
            point3 p2 = point3(p7.x(), p7.y(), p0.z());
            point3 p3 = point3(p0.x(), p7.y(), p0.z());
            point3 p4 = point3(p0.x(), p7.y(), p7.z());
            point3 p5 = point3(p0.x(), p0.y(), p7.z());
            point3 p6 = point3(p7.x(), p0.y(), p7.z());

            vertices.push_back(p0);
            vertices.push_back(p1);
            vertices.push_back(p2);
            vertices.push_back(p3);
            vertices.push_back(p4);
            vertices.push_back(p5);
            vertices.push_back(p6);
            vertices.push_back(p7);

            triangles.push_back(new Triangle(p0, p1, p2, material_)); //FRENTE
            triangles.push_back(new Triangle(p0, p2, p3, material_)); //FRENTE
            triangles.push_back(new Triangle(p5, p6, p1, material_)); //CIMA
            triangles.push_back(new Triangle(p1, p0, p5, material_)); //CIMA
            triangles.push_back(new Triangle(p0, p3, p4, material_)); //DIREITA
            triangles.push_back(new Triangle(p0, p4, p5, material_)); //DIREITA
            triangles.push_back(new Triangle(p3, p2, p4, material_)); //BAIXO
            triangles.push_back(new Triangle(p4, p2, p7, material_)); //BAIXO
            triangles.push_back(new Triangle(p1, p7, p2, material_)); //ESQUERDA
            triangles.push_back(new Triangle(p7, p1, p6, material_)); //ESQUERDA
            triangles.push_back(new Triangle(p5, p4, p7, material_)); //FUNDO
            triangles.push_back(new Triangle(p6, p5, p7, material_)); //FUNDO

            material = material_;
        }

        vector<point3*> getPoints(){
            vector<point3*> points;
            for(unsigned int i = 0; i < triangles.size(); i++){
                points.push_back(triangles[i]->getPoints()[0]);
                points.push_back(triangles[i]->getPoints()[1]);
                points.push_back(triangles[i]->getPoints()[2]);
            }
            return points;
        }

        bool hit(Ray r, float t_min, float t_max, HitRecord &ht){
            for(unsigned int i = 0; i < triangles.size(); i++){
                if(triangles[i]->hit(r, t_min, t_max, ht)){
                    return true;
                }
            }
            return false;
        }
};

#endif
