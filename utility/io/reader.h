#ifndef _READER_H_
#define _READER_H_

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
#include "basic_reader.h"
#include "light_reader.h"
#include "shader_reader.h"

using namespace std;


#define CAMERA "CAMERA"

class Reader{

    private:
        IoUtilReader util_reader;
        BasicReader basic_reader; 
        LightReader light_reader;
        ShaderReader shader_reader;

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

        Reader(){}

        Reader(string file_name){
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
                    if(basic_reader.verify_name_param(header_file, text, name)) continue;
                    if(basic_reader.verify_type_param(header_file, text, type)) continue;
                    if(basic_reader.verify_codi_param(header_file, text, codi)) continue;
                    if(basic_reader.verify_widt_param(header_file, text, width)) continue;
                    if(basic_reader.verify_heig_param(header_file, text, height)) continue;
                    if(basic_reader.verify_uplf_param(header_file, text, upper_left)) continue;
                    if(basic_reader.verify_lwlf_param(header_file, text, lower_left)) continue;
                    if(basic_reader.verify_upri_param(header_file, text, upper_right)) continue;
                    if(basic_reader.verify_lwri_param(header_file, text, lower_right)) continue;
                    if(basic_reader.verify_min_depht(header_file, text, min_depht)) continue;
                    if(basic_reader.verify_max_depht(header_file, text, max_depht)) continue;
                    if(basic_reader.verify_ray_shots(header_file, text, ray_shots)) continue;
                    if(basic_reader.verify_threads(header_file, text, nthreads)) continue;
                    if(basic_reader.verify_natural_light(header_file, text, natural_light)) continue;

                    //Leitura de luzes
                    if(light_reader.verify_light_param(header_file, text, lights)) continue;
         
                    //Leitura dos Shader, com objetos e materiais
                    if(shader_reader.verify_shader_param(header_file, text, shader, objects, 
                        d_foreground_color, 
                        d_background_color)) continue;
                   
 
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


        // Camera *read_camera(ifstream &header_file){

        // }
       
};

#endif