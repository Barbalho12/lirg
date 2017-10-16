#ifndef _LIGHT_READER_H_
#define _LIGHT_READER_H_

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

using namespace std;

#define LIGHT "LIGHT"


class LightReader{

    private:
            IoUtilReader util_reader;
            BasicReader basic_reader; 
    public:


        LightReader(){}


        bool verify_light_param(ifstream &header_file, string param, vector<Light*> &lights){
            if (param == LIGHT){
                util_reader.read_valid_char(header_file, '=');
                Light *light = read_light(header_file);
                lights.push_back(light);
                return true;
            }
            return false;  
        }

 
        Light *read_light(ifstream &header_file){

            string light_option;
            header_file >> light_option;
            util_reader.read_valid_char(header_file, '{');

            Light *ligh;

            if(light_option == "DIRECTIONAL"){
                rgb intensity;
                vec3 direction;

                int count = 2;
                while(count > 0){ 

                    string param;
                    header_file >> param;

                    if(param == "INTENSITY"){
                        intensity = util_reader.read_color(header_file);
                        util_reader.read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }
                    if(param == "DIRECTION"){
                        direction = util_reader.read_vec3(header_file);
                        util_reader.read_valid_char(header_file, ';');
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
                        intensity = util_reader.read_color(header_file);
                        util_reader.read_valid_char(header_file, ';'); 
                        count--;
                        continue;
                    }

                    if(param == "ORIGIN"){
                        origin = util_reader.read_vec3(header_file);
                        util_reader.read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }

                    if(param == "DIRECTION"){
                        direction = util_reader.read_vec3(header_file);
                        util_reader.read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }

                    if(param == "ANGLE"){
                        header_file >> angle;
                        util_reader.read_valid_char(header_file, ';');
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
                        intensity = util_reader.read_color(header_file);
                        util_reader.read_valid_char(header_file, ';');
                        count--;
                        continue;
                    }

                    if(param == "ORIGIN"){
                        origin = util_reader.read_vec3(header_file);
                        util_reader.read_valid_char(header_file, ';');
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

      
};

#endif