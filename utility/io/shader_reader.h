#ifndef _SHADER_READER_H_
#define _SHADER_READER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../vec3.h"
#include "../ray.h"
#include "../sphere.h"
#include "../mash.h"
#include "../triangle.h"
#include "../box.h"
#include "../object.h"
#include "../lambertian.h"
#include "../metal.h"
#include "../dielectric.h"
#include "../toon.h"
#include <cmath>        // sqrt, fabs

#include "io_util_reader.h"
#include "basic_reader.h"

using namespace std;

#define SPHERE "SPHERE"
#define TRIANGLE "TRIANGLE"
#define BOX "BOX"
#define MASH "MASH"
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

                //Verifica comentários
                if(util_reader.verify_by_coments(header_file, text.back())){
                    continue;
                }


                if(text == SPHERE){
                    util_reader.read_valid_char(header_file, '=');
                    Sphere *sphere = read_sphere(header_file);
                    objects.push_back(sphere);  
                    continue;
                }

                if(text == TRIANGLE){
                    util_reader.read_valid_char(header_file, '=');
                    Triangle *triangle = read_triangle(header_file);
                    objects.push_back(triangle);  
                    continue;
                }

                if(text == BOX){
                    util_reader.read_valid_char(header_file, '=');
                    Box *box = read_box(header_file);
                    objects.push_back(box);  
                    continue;
                }

                if(text == MASH){
                    util_reader.read_valid_char(header_file, '=');
                    // vector<Triangle*> mash = read_mash(header_file);
                    // for (int i = 0; i < mash.size(); i++){
                    //     objects.push_back(mash[i]);
                    // }


                    // Mash *mash = read_mash(header_file);
                    // for (int i = 0; i < mash->mash.size(); i++){
                    //     objects.push_back(mash->mash[i]);
                    // }


                    Mash *mash = read_mash(header_file);
                    objects.push_back(mash);

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

            Material *mat = nullptr;

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
            float rd;
            string material;
            bool texture;

            Material *mat = nullptr;

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

                if(param == "ENABLE_TEXTURE"){
                    string text;
                    header_file >> text;
                    
                    if(text == "True"){
                        texture = true;
                    }else{
                        texture = false;
                    }
                    
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }

                if(param == "REFRACT_DEGREE"){
                    header_file >> rd;
                    util_reader.read_valid_char(header_file, ';');
                    continue;
                }
                
                util_reader.validate_string(param, "}");
                break; 
            }

            if(material == "METAL"){
                mat = new Metal(albedo);
            }else if(material == "LAMBERTIAN"){
                mat = new Lambertian(albedo, texture);
            }else if(material == "DIELECTRIC"){
                mat = new Dielectric(albedo, rd);
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
                material = new Lambertian(vec3(0,0,0), false);
                
            }

            return material;
        }

        Sphere *read_sphere(ifstream &header_file){

            point3 center;
            float radius;
            Material *material;

            int count = 3; //Numero de atributos que serão lidos 
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

            return new Sphere(center, radius, material);
        }


        Triangle *read_triangle(ifstream &header_file){

            vec3 p0;
            vec3 p1;
            vec3 p2;
            Material *material;



            int count = 4; //Numero de atributos que serão lidos 
            while(count > 0){   
                string param;
                header_file >> param;

                if(param == "P0"){
                    p0 = util_reader.read_vec3(header_file);
                    util_reader.read_valid_char(header_file, ';'); 
                    count--;
                    continue;
                }

                if(param == "P1"){
                    p1 = util_reader.read_vec3(header_file);
                    util_reader.read_valid_char(header_file, ';'); 
                    count--;
                    continue;
                }

                if(param == "P2"){
                    p2 = util_reader.read_vec3(header_file);
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

            return new Triangle(p0, p1, p2, material);

        }

        Box *read_box(ifstream &header_file){

            vec3 p0;
            vec3 p7;
            Material *material;



            int count = 3; //Numero de atributos que serão lidos 
            while(count > 0){   
                string param;
                header_file >> param;

                if(param == "P0"){
                    p0 = util_reader.read_vec3(header_file);
                    util_reader.read_valid_char(header_file, ';'); 
                    count--;
                    continue;
                }

                if(param == "P7"){
                    p7 = util_reader.read_vec3(header_file);
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

            return new Box(p0, p7, material);

        }

        Mash *read_mash(ifstream &header_file){
            string objectPath;
            Material *material;
            vector<point3> points;
            vector<Triangle*> triangles;

            string txt;
            header_file >> txt;
            material = read_material(header_file);
            util_reader.read_valid_char(header_file, ';');

            header_file >> objectPath;
            util_reader.read_valid_char(header_file, ';'); 

            ifstream objectDescription(objectPath);

            while(!objectDescription.eof()){
                objectDescription >> txt;

                if(txt == "v"){
                    float x, y, z;
                    objectDescription >> x;
                    objectDescription >> y;
                    objectDescription >> z;

                    points.push_back(point3(x, y, z));
                }

                if (txt == "f"){
                    float p1, p2, p3;
                    objectDescription >> p1;
                    objectDescription >> p2;
                    objectDescription >> p3;

                    triangles.push_back(new Triangle(points[p1-1], points[p2-1], points[p3-1], material));
                }
            }

            Mash* mash = new Mash(triangles, "BOX");
            // Mash* mash = new Mash(triangles, "SPHERE");
            return mash;
        }
};

#endif