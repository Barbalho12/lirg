#ifndef _MASH_H_
#define _MASH_H_

#include <typeinfo>
#include "object.h"
#include "vec3.h"
#include "triangle.h"
#include <vector>
#include "sphere.h"
#include "box.h"

using namespace utility;
using namespace std;

class Mash : public Object {

    public:

        vector<Triangle*> mash;
        Object* object;
        vector<Object*> containers;

        vector<point3*> points;

        Mash(vector<Triangle*> mash_, Object* object_){
            mash = mash_;
            object = object_;

            setPoints();
        }

        Mash(vector<Triangle*> mash_){
            mash = mash_;
            object = new Box(point3(0,0,0),point3(0,0,0),material);
            setPoints();
            resizeContainer();
        }

        Mash(vector<Triangle*> mash_, string container_ref){
            mash = mash_;
            if(container_ref == "BOX"){
                object = new Box(point3(0,0,0),point3(0,0,0),material);
            }else if (container_ref == "SPHERE"){
                object = new Sphere(point3(0,0,0),0);
            }
            
            setPoints();
            resizeContainer();
        }

        void setPoints(){
            for(unsigned int i = 0; i < mash.size(); i++){
                points.push_back(mash[i]->getPoints()[0]);
                points.push_back(mash[i]->getPoints()[1]);
                points.push_back(mash[i]->getPoints()[2]);
            }
        }

        void resizeContainer(){
            float x_max =-100000;
            float x_min =100000;
            float y_max =-100000;
            float y_min =100000;
            float z_max =-100000;
            float z_min =100000;

            for(unsigned int i = 0; i < points.size(); i++){
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

            if(typeid(*object) == typeid(Sphere)){
                //centro da esfera
                point3 center = point3((x_max+x_min)/2, (y_max+y_min)/2, (z_max+z_min)/2);

                //raio
                float radius = sqrt( pow(x_max - x_min, 2) + pow(y_max-y_min, 2) + pow(z_max-z_min, 2))/2;

                object = new Sphere(center, radius);

            }else if(typeid(*object) == typeid(Box)){

                point3 p0 = point3(x_max, y_max, z_max);
                point3 p7 = point3(x_min, y_min, z_min);
                Box* box = new Box(p0, p7, material);
                object = box;
                create_containers();
                fill_containers();
            }
            
        }

        vector<point3*> getPoints(){
            return points;
        }

        bool hit(Ray r, float t_min, float t_max, HitRecord &ht){
            bool result = false;
            if(object->hit(r, t_min, t_max, ht)){

                if(typeid(*object) == typeid(Sphere) || containers.size() == 0){

                    for (unsigned int i = 0; i < mash.size(); i++){
                        result =  mash[i]->hit(r, t_min, t_max, ht);
                        if(result){
                            break;
                        }
                    }

                } else if(typeid(*object) == typeid(Box)){

                    Box *box = dynamic_cast<Box*>(object);

                    for (unsigned int i = 0; i < containers.size(); i++){
                        Box *box_container = dynamic_cast<Box*>(containers[i]);
                        if(box_container->hit(r, t_min, t_max, ht)){
                            for (unsigned int j = 0; j < box_container->getContent().size(); j++){
                                if(box_container->getContent()[j]->hit(r, t_min, t_max, ht)){
                                    return true;
                                }
                            }
                        }
                    }


                    for (unsigned int j = 0; j < box->getContent().size(); j++){
                        if(box->getContent()[j]->hit(r, t_min, t_max, ht)){
                            result = true;
                            break;
                        }
                    }
                }
            }
            return result;
        }


        void create_containers(){

            vector<Object*> containers_;
            Box *box = dynamic_cast<Box*>(object);

            float x_init = box->vertices[7].x();
            float y_init = box->vertices[7].y();
            float z_init = box->vertices[7].z();

            float dx = (box->vertices[0].x() - box->vertices[1].x());
            float dy = (box->vertices[0].y() - box->vertices[3].y());
            float dz = (box->vertices[0].z() - box->vertices[5].z());

            float dx_ = (dx/4.0);
            float dy_ = (dy/4.0);
            float dz_ = (dz/4.0);

            for(float i = 0; i < 4; i += 1){

                for(float j = 0; j < 4; j += 1){

                    for(float k = 0; k < 4; k += 1){
                        float x = x_init+(i*dx_);
                        float y = y_init+(j*dy_);
                        float z = z_init+(k*dz_);

                        point3 p0 = point3( x+dx_ , y+dy_ , z+dz_);
                        point3 p7 = point3( x, y, z);
                        containers_.push_back(new Box(p0 , p7, material));
                    }

                }
                
            }

            containers = containers_;
        }

        void fill_containers(){

             if(typeid(*object) == typeid(Box)){

                for(unsigned int j = 0; j < mash.size(); j++){
                    bool is_somewhere = false;


                    for(unsigned int i = 0; i < containers.size(); i++){
                        Box *box = dynamic_cast<Box*>(containers[i]);
                        if(box->its_inside(mash[j])){
                            box->add_inside(mash[j]);
                            is_somewhere = true;
                            break;
                        }
                    }

                    if(!is_somewhere){
                        Box *box = dynamic_cast<Box*>(object);
                        box->add_inside(mash[j]);
                    }
                }

            }

            cout <<  "Qtd containers: "<< containers.size() << endl;

            cout << "Nowhere: "<< dynamic_cast<Box*>(object)->getContent().size() << endl;
            for(unsigned int i = containers.size()-1; i > 0; i--){
                Box *box = dynamic_cast<Box*>(containers[i]);
                if(box->getContent().size() == 0){
                    containers.erase(containers.begin()+i);
                }
            }
            cout <<  "Qtd final containers: "<< containers.size() << endl;

        }
};

#endif
