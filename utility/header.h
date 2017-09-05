#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "object.h"
#include "lambertian.h"
#include "metal.h"

using namespace std;

#define NAME_PARAM "NAME"
#define TYPE_PARAM "TYPE"
#define CODI_PARAM "CODIFICATION"
#define WIDT_PARAM "WIDTH"
#define HEIG_PARAM "HEIGHT"
#define UPLF_PARAM "UPPER_LEFT"
#define LWLF_PARAM "LOWER_LEFT"
#define UPRI_PARAM "UPPER_RIGHT"
#define LWRI_PARAM "LOWER_RIGHT"

#define MIN_DEPHT "MIN_DEPHT"
#define MAX_DEPHT "MAX_DEPHT"

#define RAY_SHOTS "RAY_SHOTS"

#define DEPTH_MODE "DEPTH_MODE"

#define SPHERE "SPHERE"

#define SHADER_ "SHADER"

#define LOWER_LEFT_CORNER "LOWER_LEFT_CORNER" // lower left corner of the view plane.
#define H_D_VIEW_PLANE "H_D_VIEW_PLANE"       // Horizontal dimension of the view plane.
#define V_D_VIEW_PLANE "V_D_VIEW_PLANE"       // Vertical dimension of the view plane.
#define CAMERA_ORIGIN "CAMERA_ORIGIN"         // the camera's origin.

#define THREADS "THREADS"

typedef enum{
    NORMALS2RGB,
    BLINNPHONG,
    DEPTHCOLOR,
    LAMBERTIAN
}SHADER;

class Header{

    public:
        string name;
        string type;
        string codi; //CODIFICATION
        int width;
        int height;
        rgb upper_left; //UPPER_LEFT
        rgb lower_left; //LOWER_LEFT
        rgb upper_right; //UPPER_RIGHT
        rgb lower_right; //LOWER_RIGHT

        float min_depht;
        float max_depht;

        int ray_shots;

        SHADER shader;

        vector<Object*> objects;

        point3 lower_left_corner;
        vec3 h_d_view_plane;
        vec3 v_d_view_plane;
        point3 camera_origin;

        int nthreads = 1;

        Header(){
           
        }

        Header(string file_name){
            readFromFile(file_name);
        }

        void readFromFile(string file_name){
            ifstream header_file;
            header_file.open(file_name);

            if(header_file.is_open()){
                while(!header_file.eof()){
                    string text;
                    header_file >> text;
         
                    if (text == NAME_PARAM){
                        header_file >> text;
                        header_file >> name;
                    }

                    if (text == TYPE_PARAM){
                        header_file >> text;
                        header_file >> type;
                    }

                    if (text == CODI_PARAM){
                        header_file >> text;
                        header_file >> codi;
                    }

                    if(text == WIDT_PARAM){
                        header_file >> text;
                        header_file >> width;
                    }

                    if(text == HEIG_PARAM){
                        header_file >> text;
                        header_file >> height;
                    }

                    if(text == UPLF_PARAM){
                        header_file >> text;
                        upper_left = read_vec3(header_file);
                    }

                    if(text == LWLF_PARAM){
                        header_file >> text;
                        lower_left = read_vec3(header_file);
                    }

                    if(text == UPRI_PARAM){
                        header_file >> text;
                        upper_right = read_vec3(header_file);
                    }

                    if(text == LWRI_PARAM){
                        header_file >> text;
                        lower_right = read_vec3(header_file);
                    }

                    if(text == MIN_DEPHT){
                        header_file >> text;
                        header_file >> min_depht;
                    }

                    if(text == MAX_DEPHT){
                        header_file >> text;
                        header_file >> max_depht;
                    }

                    if(text == RAY_SHOTS){
                        header_file >> text;
                        header_file >> ray_shots;
                    }

                    if(text == SHADER_){
                        header_file >> text;
                        string shader_option;
                        header_file >> shader_option;

                        if(shader_option == "NORMALS2RGB"){
                            shader = NORMALS2RGB;
                        }else if(shader_option == "BLINNPHONG"){
                            shader = BLINNPHONG;
                        }else if(shader_option == "DEPTHCOLOR"){
                            shader = DEPTHCOLOR;
                        }else if(shader_option == "LAMBERTIAN"){
                            shader = LAMBERTIAN;
                        }
                    }

                    if(text == SPHERE){
                        header_file >> text;
                        point3 c = read_vec3(header_file);
                        float r;
                        header_file >> r;
                        string material;
                        header_file >> material;
                        if(material == "NONE"){
                            objects.push_back(new Sphere(c, r, new Lambertian(vec3(0,0,0))));         
                        }else if(material == "LAMBERTIAN"){
                            objects.push_back(new Sphere(c, r, new Lambertian(read_vec3(header_file))));
                        }else if(material == "METAL"){
                            objects.push_back(new Sphere(c, r, new Metal(read_vec3(header_file))));
                        }
                    }

                    if(text == LOWER_LEFT_CORNER){
                        header_file >> text;
                        lower_left_corner = read_vec3(header_file);
                    }

                    if(text == H_D_VIEW_PLANE){
                        header_file >> text;
                        h_d_view_plane = read_vec3(header_file);
                    }

                    if(text == V_D_VIEW_PLANE){
                        header_file >> text;
                        v_d_view_plane = read_vec3(header_file);
                    }

                    if(text == CAMERA_ORIGIN){
                        header_file >> text;
                        camera_origin = read_vec3(header_file);
                    }
                    if(text == THREADS){
                        header_file >> text;
                        header_file >> nthreads;
                    }
                    
                }
            }else{
                cout << "file is not open" << endl;
            }

            header_file.close();
        }

        vec3 read_vec3(ifstream &header_file){
            float a,b,c;
            header_file >> a;
            header_file >> b;
            header_file >> c;
            return vec3(a,b,c);
        }
};

#endif