#ifndef _SHADER_READER_H_
#define _SHADER_READER_H_

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

#include "io_util_reader.h"
#include "basic_reader.h"

using namespace std;

#define SPHERE "SPHERE"
#define SHADER_ "SHADER"

#define BP_AMBIENT "AMBIENT"
#define BP_SPECULAR "SPECULAR"
#define BP_SHININESS "SHININESS"

#define D_FOREGROUND_COLOR "D_FOREGROUND_COLOR" 
#define D_BACKGROUND_COLOR "D_BACKGROUND_COLOR" 

typedef enum{
    NORMALS2RGB,
    BLINNPHONG,
    DEPTHCOLOR,
    LAMBERTIAN,
    BP_LAMBERTIAN,
    TOON
}SHADER;

class ShaderReader{


    private:
        IoUtilReader util_reader;
        BasicReader basic_reader; 

    public:

        ShaderReader(){}

        bool verify_shader_param(ifstream &header_file, string param, 
            SHADER &shader, vector<Object*> &objects,
            rgb &d_foreground_color, rgb &d_background_color){

            if (param == SHADER_){
                util_reader.read_valid_char(header_file, '=');
                string shader_option;
                header_file >> shader_option;

                if(shader_option == "NORMALS2RGB"){
                    shader = NORMALS2RGB;
                }else if(shader_option == "BLINNPHONG"){
                    shader = BLINNPHONG;
                }else if(shader_option == "DEPTHCOLOR"){
                    shader = DEPTHCOLOR;
                    readDepthParams(header_file, d_foreground_color, d_background_color);
                }else if(shader_option == "LAMBERTIAN"){
                    shader = LAMBERTIAN;
                }else if(shader_option == "BP_LAMBERTIAN"){
                    shader = BP_LAMBERTIAN;
                }else if(shader_option == "TOON"){
                    shader = TOON;
                }

                util_reader.read_valid_char(header_file, ';');
                
                objects = read_objects(header_file);

                return true;
            }
            return false;  
        }

        void readDepthParams(ifstream &header_file, rgb &d_foreground_color, rgb &d_background_color){
            util_reader.read_valid_char(header_file, ';');
            util_reader.read_valid_string(header_file, D_FOREGROUND_COLOR);
            d_foreground_color = util_reader.read_color(header_file);
            util_reader.read_valid_char(header_file, ';');
            util_reader.read_valid_string(header_file, D_BACKGROUND_COLOR);
            d_background_color = util_reader.read_color(header_file);
        }


        vector<Object*> read_objects(ifstream &header_file){
            string text;
            util_reader.read_valid_string(header_file, "OBJECTS");
            util_reader.read_valid_char(header_file, '{');

            vector<Object*> objects;
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
            return objects;
        }


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