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

#define BP_AMBIENT "AMBIENT"
#define BP_SPECULAR "SPECULAR"
#define BP_SHININESS "SHININESS"

#define D_FOREGROUND_COLOR "D_FOREGROUND_COLOR" 
#define D_BACKGROUND_COLOR "D_BACKGROUND_COLOR" 

#define LIGHT "LIGHT"

#define NATURAL_LIGHT "NATURAL_LIGHT"

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

        rgb d_foreground_color = rgb(0,0,0);
        rgb d_background_color = rgb(0,0,0);

        float min_depht;
        float max_depht;

        int ray_shots;

        SHADER shader;
        Camera *camera;

        vector<Object*> objects;
        vector<Light*> lights;

        rgb natural_light;

        // point3 lower_left_corner;
        // vec3 h_d_view_plane;
        // vec3 v_d_view_plane;
        // point3 camera_origin;

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
                        read_valid_char(header_file, '=');
                        header_file >> name;
                    }

                    if (text == TYPE_PARAM){
                        read_valid_char(header_file, '=');
                        header_file >> type;
                    }

                    if (text == CODI_PARAM){
                        read_valid_char(header_file, '=');
                        header_file >> codi;
                    }

                    if(text == WIDT_PARAM){
                        read_valid_char(header_file, '=');
                        header_file >> width;
                    }

                    if(text == HEIG_PARAM){
                        read_valid_char(header_file, '=');
                        header_file >> height;
                    }

                    if(text == UPLF_PARAM){
                        read_valid_char(header_file, '=');
                        upper_left = read_color(header_file);
                              
                    }

                    if(text == LWLF_PARAM){
                        read_valid_char(header_file, '=');
                        lower_left = read_color(header_file);
                    }

                    if(text == UPRI_PARAM){
                        read_valid_char(header_file, '=');
                        upper_right = read_color(header_file);
                    }

                    if(text == LWRI_PARAM){
                        read_valid_char(header_file, '=');
                        lower_right = read_color(header_file);
                    }

                    // if(text == D_FOREGROUND_COLOR){
                    //     read_valid_char(header_file, '=');
                    //     d_foreground_color = read_color(header_file);
                    // }

                    // if(text == D_BACKGROUND_COLOR){
                    //     read_valid_char(header_file, '=');
                    //     d_background_color = read_color(header_file);
                    // }

                    if(text == MIN_DEPHT){
                        read_valid_char(header_file, '=');
                        header_file >> min_depht;
                    }

                    if(text == MAX_DEPHT){
                        read_valid_char(header_file, '=');
                        header_file >> max_depht;
                    }

                    if(text == RAY_SHOTS){
                        read_valid_char(header_file, '=');
                        header_file >> ray_shots;
                    }

                    if(text == SHADER_){
                        read_valid_char(header_file, '=');
                        string shader_option;
                        header_file >> shader_option;

                        if(shader_option == "NORMALS2RGB"){
                            shader = NORMALS2RGB;
                        }else if(shader_option == "BLINNPHONG"){
                            shader = BLINNPHONG;
                        }else if(shader_option == "DEPTHCOLOR"){
                            shader = DEPTHCOLOR;
                            read_valid_char(header_file, ';');
                            header_file >> text; //D_FOREGROUND_COLOR
                            d_foreground_color = read_color(header_file);
                            read_valid_char(header_file, ';');
                            header_file >> text; //D_BACKGROUND_COLOR
                            d_background_color = read_color(header_file);
                        }else if(shader_option == "LAMBERTIAN"){
                            shader = LAMBERTIAN;
                        }else if(shader_option == "BP_LAMBERTIAN"){
                            shader = BP_LAMBERTIAN;
                        }else if(shader_option == "TOON"){
                            shader = TOON;
                        }
                        read_valid_char(header_file, ';');
                        
                        read_objects(header_file);
                        
                    }

                    if(text == THREADS){
                        read_valid_char(header_file, '=');
                        header_file >> nthreads;
                    }

                    if(text == LIGHT){
                        read_valid_char(header_file, '=');
                        Light *light = read_light(header_file);
                        lights.push_back(light);
                    }

                    if(text == NATURAL_LIGHT){
                        read_valid_char(header_file, '=');
                        natural_light = read_color(header_file);
                    }

                    if(text == CAMERA){
                        read_valid_char(header_file, '=');
                        string camera_option;
                        header_file >> camera_option;

                        point3 origin;

                        if(camera_option == "DEFAULT"){
                            read_valid_char(header_file, ';');
                            point3 lower_left_corner = read_vec3(header_file);
                            read_valid_char(header_file, ';');
                            vec3 h_d_view_plane = read_vec3(header_file);
                            read_valid_char(header_file, ';');
                            vec3 v_d_view_plane = read_vec3(header_file);
                            read_valid_char(header_file, ';');
                            origin = read_vec3(header_file);
                            camera = new Camera(lower_left_corner, v_d_view_plane, h_d_view_plane, origin);
                        }else if(camera_option == "POSITIONABLE"){
                            read_valid_char(header_file, ';');
                            origin = read_vec3(header_file);
                            read_valid_char(header_file, ';');
                            vec3 lookAt = read_vec3(header_file);
                            read_valid_char(header_file, ';');
                            vec3 vUp = read_vec3(header_file);
                            read_valid_char(header_file, ';');
                            float vFlow;
                            header_file >> vFlow;
                            read_valid_char(header_file, ';');
                            float aperture;
                            header_file >> aperture;
                            read_valid_char(header_file, ';');
                            vec3 focusPoint = read_vec3(header_file);
                            camera = new Camera(origin, lookAt, vUp, vFlow, float(width)/float(height), aperture, (origin-focusPoint).length());
                        }
                    }
                }
            }else{
                cout << "file is not open" << endl;
            }

            header_file.close();
        }

        void read_valid_char(ifstream &header_file, char expected_char){
            char character;
            header_file >> character; 
            if(character != expected_char){
                cout << "ERRO: no expected character: '"<< character <<"',  expected: '" << expected_char << "'" << endl;
                exit (EXIT_FAILURE);
            }
        }
        void read_valid_string(ifstream &header_file, string expected_string){
            string text;
            header_file >> text; 
            if(text != expected_string){
                cout << "ERRO: no expected string: '"<< text <<"',  expected: '" << expected_string << "'" << endl;
                exit (EXIT_FAILURE);
            }

        }

        void validate_string(string text, string expected_string){
            if(text != expected_string){
                cout << "ERRO: no expected string: '"<< text <<"',  expected: '" << expected_string << "'" << endl;
                exit (EXIT_FAILURE);
            }

        }

        void read_objects(ifstream &header_file){
            string text;
            read_valid_string(header_file, "OBJECTS");
            read_valid_char(header_file, '{');

            while(true){
                string text;
                header_file >> text;

                if(text == SPHERE){
                    read_valid_char(header_file, '=');
                    Sphere *sphere = read_sphere(header_file);
                    objects.push_back(sphere);  
                    continue;
                }

                break;
            }
            // cout << "List Objects read" << endl;
        }

        vector<rgb> readListColor(ifstream &header_file){
            char c;
            vector<rgb> colors;
            header_file.get(c);
            while(c != '{') header_file.get(c);
            while(true){
                string type;
                header_file >> type;
                if(type == "RGB"){
                    colors.push_back(read_vec3(header_file)/255.99f);
                }else if(type == "URGB"){
                    colors.push_back(read_vec3(header_file));
                }else{
                    break;
                }
            }
            return colors;
        }


        vec3 read_vec3(ifstream &header_file){
            float a,b,c;
            header_file >> a;
            header_file >> b;
            header_file >> c;
            return vec3(a,b,c);
        }

        vec3 read_color(ifstream &header_file){

            string type;
            header_file >> type;

            vec3 color;

            if(type == "RGB"){
                color = read_vec3(header_file)/255.99f;
            }else if(type == "URGB"){
                color = read_vec3(header_file);
            }

            return color;
        }

        Light *read_light(ifstream &header_file){

            string light_option;
            header_file >> light_option;
            read_valid_char(header_file, '{');

            Light *ligh;

            if(light_option == "DIRECTIONAL"){
                rgb intensity;
                vec3 direction;

                int count = 2;
                while(count > 0){ 

                    string param;
                    header_file >> param;

                    if(param == "INTENSITY"){
                        intensity = read_color(header_file);
                        // header_file >> nullable; 
                        read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }
                    if(param == "DIRECTION"){
                        direction = read_vec3(header_file);
                        // header_file >> nullable; 
                        read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }
                    break;
                }

                ligh =  new DirectionLight(intensity, direction);
            
            }else if(light_option == "SPOT"){

                rgb intensity;
                vec3 origin;
                vec3 direction;
                float angle;

                int count = 4;
                while(count > 0){ 
                    string param;
                    header_file >> param;

                    if(param == "INTENSITY"){
                        intensity = read_color(header_file);
                        // header_file >> nullable;
                        read_valid_char(header_file, ';'); 
                        count--;
                        continue;
                    }

                    if(param == "ORIGIN"){
                        origin = read_vec3(header_file);
                        // header_file >> nullable; 
                        read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }

                    if(param == "DIRECTION"){
                        direction = read_vec3(header_file);
                        // header_file >> nullable; 
                        read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }

                    if(param == "ANGLE"){
                        header_file >> angle;
                        // header_file >> nullable; 
                        read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }

                    break;

                }

                ligh = new SpotLight(intensity, origin, direction, angle);

            }else if(light_option == "POINT"){

                rgb intensity;
                vec3 origin;

                int count = 2;
                while(count > 0){ 
                    string param;
                    header_file >> param;

                    if(param == "INTENSITY"){
                        intensity = read_color(header_file);
                        // header_file >> nullable; 
                        read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }

                    if(param == "ORIGIN"){
                        origin = read_vec3(header_file);
                        // header_file >> nullable; 
                        read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }

                    break;

                }

                ligh = new PointLight(origin, intensity);
            }

            // cout << "List of lights read" << endl;
            return ligh;
        }

        // Camera *read_camera(ifstream &header_file){

        // }

        Toon *read_toon_material(ifstream &header_file){
            read_valid_char(header_file, '{');

            rgb border;
            rgb shadow;
            vector<rgb> colors;

            while(true){
                string param;
                header_file >> param;  

                if(param == "BORDER"){
                    border = read_color(header_file);
                    read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "SHADOW"){
                    shadow = read_color(header_file);
                    read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "COLORS"){
                    colors = readListColor(header_file);
                    read_valid_char(header_file, ';');
                    continue;
                }

                validate_string(param, "}");
                break;
            }

            return new Toon(colors, border, shadow);
        }

        Material *read_blinnphong_material(ifstream &header_file){
            read_valid_char(header_file, '{');

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
                    read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "ALBEDO"){
                    albedo = read_color(header_file);
                    read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "AMBIENT"){
                    ambient = read_color(header_file);
                    read_valid_char(header_file, ';'); 
                    continue;
                }
                if(param == "SPECULAR"){
                    specular = read_color(header_file);
                    read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "SHININESS"){
                    header_file >> shininess;
                    read_valid_char(header_file, ';');
                    continue;
                }

                validate_string(param, "}");
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
            read_valid_char(header_file, '{');

            rgb albedo;
            string material;

            Material *mat;

            while(true){
                string param;
                header_file >> param; 

                if(param == "MATERIAL"){
                    header_file >> material; 
                    read_valid_char(header_file, ';');
                    continue;
                }
                if(param == "ALBEDO"){
                    albedo = read_color(header_file);
                    read_valid_char(header_file, ';');
                    continue;
                }
                
                validate_string(param, "}");
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
                    center = read_vec3(header_file);
                    read_valid_char(header_file, ';'); 
                    count--;
                    continue;
                }

                if(param == "RADIUS"){
                    header_file >> radius;
                    read_valid_char(header_file, ';'); 
                    count--;
                    continue;
                }

                if (param == "TYPE"){
                    material = read_material(header_file);
                    read_valid_char(header_file, ';');  

                    count--;
                    continue;
                }

                validate_string(param, "**"); //Se chegar aqui é ERRO
                break;
            }

            // cout << "Sphere read" << endl;
            return new Sphere(center, radius, material);
            
        }
};

#endif