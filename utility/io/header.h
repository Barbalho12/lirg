#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../vec3.h"
#include "../ray.h"
#include "../sphere.h"
#include "../object.h"
#include "../lambertian.h"
#include "../metal.h"
#include "../toon.h"
#include "../light.h"
#include "../direction_light.h"
#include "../spot_light.h"
#include "../point_light.h"
#include "../camera.h"
#include "io_util_reader.h"
#include "basic_header.h"
#include "light_reader.h"

using namespace std;


#define SPHERE "SPHERE"
#define SHADER_ "SHADER"

// #define LOWER_LEFT_CORNER "LOWER_LEFT_CORNER" // lower left corner of the view plane.
// #define H_D_VIEW_PLANE "H_D_VIEW_PLANE"       // Horizontal dimension of the view plane.
// #define V_D_VIEW_PLANE "V_D_VIEW_PLANE"       // Vertical dimension of the view plane.
// #define CAMERA_ORIGIN "CAMERA_ORIGIN"         // the camera's origin.

#define BP_AMBIENT "AMBIENT"
#define BP_SPECULAR "SPECULAR"
#define BP_SHININESS "SHININESS"

#define D_FOREGROUND_COLOR "D_FOREGROUND_COLOR" 
#define D_BACKGROUND_COLOR "D_BACKGROUND_COLOR" 

#define LIGHT "LIGHT"

#define CAMERA "CAMERA"


typedef enum{
    NORMALS2RGB,
    BLINNPHONG,
    DEPTHCOLOR,
    LAMBERTIAN,
    BP_LAMBERTIAN,
    TOON
}SHADER;

class Header{


    private:
        IoUtilReader util_reader;
        BasicHeader basic_header; 
        LightReader light_reader;

    public:
        string name;
        string type;
        string codi; //CODIFICATION
        int width;
        int height;
        rgb upper_left = rgb(0,0,0); //UPPER_LEFT
        rgb lower_left = rgb(0,0,0); //LOWER_LEFT
        rgb upper_right = rgb(0,0,0); //UPPER_RIGHT
        rgb lower_right = rgb(0,0,0); //LOWER_RIGHT
        float min_depht;
        float max_depht;
        int ray_shots;
        int nthreads = 1;

        
        rgb d_foreground_color = rgb(0,0,0);
        rgb d_background_color = rgb(0,0,0);
        
        SHADER shader;
        Camera *camera;

        vector<Object*> objects;
        vector<Light*> lights;
        rgb natural_light;

        Header(){}

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

                    //Configurações básicas
                    if(basic_header.verify_name_param(header_file, text, name)) continue;
                    if(basic_header.verify_type_param(header_file, text, type)) continue;
                    if(basic_header.verify_codi_param(header_file, text, codi)) continue;
                    if(basic_header.verify_widt_param(header_file, text, width)) continue;
                    if(basic_header.verify_heig_param(header_file, text, height)) continue;
                    if(basic_header.verify_uplf_param(header_file, text, upper_left)) continue;
                    if(basic_header.verify_lwlf_param(header_file, text, lower_left)) continue;
                    if(basic_header.verify_upri_param(header_file, text, upper_right)) continue;
                    if(basic_header.verify_lwri_param(header_file, text, lower_right)) continue;
                    if(basic_header.verify_min_depht(header_file, text, min_depht)) continue;
                    if(basic_header.verify_max_depht(header_file, text, max_depht)) continue;
                    if(basic_header.verify_ray_shots(header_file, text, ray_shots)) continue;
                    if(basic_header.verify_threads(header_file, text, nthreads)) continue;
                    if(basic_header.verify_natural_light(header_file, text, natural_light)) continue;

                    //Leitura de luzes
                    if(light_reader.verify_light_param(header_file, text, lights)) continue;
         
                    if(text == SHADER_){
                        util_reader.read_valid_char(header_file, '=');
                        string shader_option;
                        header_file >> shader_option;

                        if(shader_option == "NORMALS2RGB"){
                            shader = NORMALS2RGB;
                        }else if(shader_option == "BLINNPHONG"){
                            shader = BLINNPHONG;
                        }else if(shader_option == "DEPTHCOLOR"){
                            shader = DEPTHCOLOR;
                            util_reader.read_valid_char(header_file, ';');
                            header_file >> text; //D_FOREGROUND_COLOR
                            d_foreground_color = util_reader.read_color(header_file);
                            util_reader.read_valid_char(header_file, ';');
                            header_file >> text; //D_BACKGROUND_COLOR
                            d_background_color = util_reader.read_color(header_file);
                        }else if(shader_option == "LAMBERTIAN"){
                            shader = LAMBERTIAN;
                        }else if(shader_option == "BP_LAMBERTIAN"){
                            shader = BP_LAMBERTIAN;
                        }else if(shader_option == "TOON"){
                            shader = TOON;
                        }
                        util_reader.read_valid_char(header_file, ';');
                        
                        read_objects(header_file);
                        
                    }

                   

                    if(text == CAMERA){
                        util_reader.read_valid_char(header_file, '=');
                        string camera_option;
                        header_file >> camera_option;

                        point3 origin;

                        if(camera_option == "DEFAULT"){
                            util_reader.read_valid_char(header_file, ';');
                            point3 lower_left_corner = util_reader.read_vec3(header_file);
                            util_reader.read_valid_char(header_file, ';');
                            vec3 h_d_view_plane = util_reader.read_vec3(header_file);
                            util_reader.read_valid_char(header_file, ';');
                            vec3 v_d_view_plane = util_reader.read_vec3(header_file);
                            util_reader.read_valid_char(header_file, ';');
                            origin = util_reader.read_vec3(header_file);
                            camera = new Camera(lower_left_corner, v_d_view_plane, h_d_view_plane, origin);
                        }else if(camera_option == "POSITIONABLE"){
                            util_reader.read_valid_char(header_file, ';');
                            origin = util_reader.read_vec3(header_file);
                            util_reader.read_valid_char(header_file, ';');
                            vec3 lookAt = util_reader.read_vec3(header_file);
                            util_reader.read_valid_char(header_file, ';');
                            vec3 vUp = util_reader.read_vec3(header_file);
                            util_reader.read_valid_char(header_file, ';');
                            float vFlow;
                            header_file >> vFlow;
                            util_reader.read_valid_char(header_file, ';');
                            float aperture;
                            header_file >> aperture;
                            util_reader.read_valid_char(header_file, ';');
                            vec3 focusPoint = util_reader.read_vec3(header_file);
                            camera = new Camera(origin, lookAt, vUp, vFlow, float(width)/float(height), aperture, (origin-focusPoint).length());
                        }
                    }
                }
            }else{
                cout << "file is not open" << endl;
            }

            header_file.close();
        }

        void read_objects(ifstream &header_file){
            string text;
            util_reader.read_valid_string(header_file, "OBJECTS");
            util_reader.read_valid_char(header_file, '{');

            while(true){
                string text;
                header_file >> text;

                if(text == SPHERE){
                    util_reader.read_valid_char(header_file, '=');
                    Sphere *sphere = read_sphere(header_file);
                    objects.push_back(sphere);  
                    continue;
                }

                break;
            }
            // cout << "List Objects read" << endl;
        }

        // Camera *read_camera(ifstream &header_file){

        // }

        Toon *read_toon_material(ifstream &header_file){
            util_reader.read_valid_char(header_file, '{');

            rgb border;
            rgb shadow;
            vector<rgb> colors;

            while(true){
                string param;
                header_file >> param;  

                if(param == "BORDER"){
                    border = util_reader.read_color(header_file);
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "SHADOW"){
                    shadow = util_reader.read_color(header_file);
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "COLORS"){
                    colors = util_reader.readListColor(header_file);
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }

                util_reader.validate_string(param, "}");
                break;
            }

            return new Toon(colors, border, shadow);
        }

        Material *read_blinnphong_material(ifstream &header_file){
            util_reader.read_valid_char(header_file, '{');

            rgb albedo;
            rgb ambient;
            rgb specular;
            float shininess;
            string material;

            Material *mat;

            while(true){
                string param;
                header_file >> param;  

                if(param == "MATERIAL"){
                    header_file >> material; 
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "ALBEDO"){
                    albedo = util_reader.read_color(header_file);
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "AMBIENT"){
                    ambient = util_reader.read_color(header_file);
                    util_reader.read_valid_char(header_file, ';'); 
                    continue;
                }
                if(param == "SPECULAR"){
                    specular = util_reader.read_color(header_file);
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "SHININESS"){
                    header_file >> shininess;
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }

                util_reader.validate_string(param, "}");
                break;     
            }
            
            if(material == "METAL"){
                mat = new Metal(albedo,ambient,specular,shininess);
            }else if(material == "LAMBERTIAN"){
                mat = new Lambertian(albedo,ambient,specular,shininess);
            }
            return mat;

        }

        Material *read_lambertian_material(ifstream &header_file){
            util_reader.read_valid_char(header_file, '{');

            rgb albedo;
            string material;

            Material *mat;

            while(true){
                string param;
                header_file >> param; 

                if(param == "MATERIAL"){
                    header_file >> material; 
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "ALBEDO"){
                    albedo = util_reader.read_color(header_file);
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }
                
                util_reader.validate_string(param, "}");
                break; 
            }

            if(material == "METAL"){
                mat = new Metal(albedo);
            }else if(material == "LAMBERTIAN"){
                mat = new Lambertian(albedo);
            }

            return mat;
        }


        Material *read_material(ifstream &header_file){
            string type;
            header_file >> type;
            Material *material;

            if(type == "TOON"){
                material = read_toon_material(header_file);
            }else if(type == "BLINNPHONG" || type == "BP_LAMBERTIAN"){
                material = read_blinnphong_material(header_file);
            }else if(type == "LAMBERTIAN"){
                material = read_lambertian_material(header_file);
            }else{ //type == "NORMALS2RGB" || type == "DEPTHCOLOR"
                material = new Lambertian(vec3(0,0,0));  
                
            }

            return material;
        }

        Sphere *read_sphere(ifstream &header_file){

            point3 center;
            float radius;
            Material *material;

            int count = 3;
            while(count > 0){   
                string param;
                header_file >> param;

                if(param == "CENTER"){
                    center = util_reader.read_vec3(header_file);
                    util_reader.read_valid_char(header_file, ';'); 
                    count--;
                    continue;
                }

                if(param == "RADIUS"){
                    header_file >> radius;
                    util_reader.read_valid_char(header_file, ';'); 
                    count--;
                    continue;
                }

                if (param == "TYPE"){
                    material = read_material(header_file);
                    util_reader.read_valid_char(header_file, ';');  

                    count--;
                    continue;
                }

                util_reader.validate_string(param, "**"); //Se chegar aqui é ERRO
                break;
            }

            // cout << "Sphere read" << endl;
            return new Sphere(center, radius, material);
        }
};

#endif