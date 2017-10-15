#ifndef _BASICHEADER_H_
#define _BASICHEADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../vec3.h"
#include "io_util_reader.h"

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
#define THREADS "THREADS"
#define NATURAL_LIGHT "NATURAL_LIGHT"


class BasicHeader{

    private:
        IoUtilReader util_reader;

    public:
    
        BasicHeader(){}

        bool verify_name_param(ifstream &header_file, string param, string &name){
            if (param == NAME_PARAM){
                util_reader.read_valid_char(header_file, '=');
                header_file >> name;
                return true;
            }
            return false;  
        }

        bool verify_type_param(ifstream &header_file, string param, string &type){
            if (param == TYPE_PARAM){
                util_reader.read_valid_char(header_file, '=');
                header_file >> type;
                return true;
            }
            return false;  
        }

        bool verify_codi_param(ifstream &header_file, string param, string &codi){
            if (param == CODI_PARAM){
                util_reader.read_valid_char(header_file, '=');
                header_file >> codi;
                return true;
            }
            return false;  
        }

        bool verify_widt_param(ifstream &header_file, string param, int &width){
            if (param == WIDT_PARAM){
                util_reader.read_valid_char(header_file, '=');
                header_file >> width;
                return true;
            }
            return false;  
        }

        bool verify_heig_param(ifstream &header_file, string param, int &height){
            if (param == HEIG_PARAM){
                util_reader.read_valid_char(header_file, '=');
                header_file >> height;
                return true;
            }
            return false;  
        }

        bool verify_uplf_param(ifstream &header_file, string param, rgb &upper_left){
            if (param == UPLF_PARAM){
                util_reader.read_valid_char(header_file, '=');
                upper_left = util_reader.read_color(header_file);
                return true;
            }
            return false;  
        }



        bool verify_lwlf_param(ifstream &header_file, string param, rgb &lower_left){
            if (param == LWLF_PARAM){
                util_reader.read_valid_char(header_file, '=');
                lower_left = util_reader.read_color(header_file);
                return true;
            }
            return false;  
        }

        bool verify_upri_param(ifstream &header_file, string param, rgb &upper_right){
            if (param == UPRI_PARAM){
                util_reader.read_valid_char(header_file, '=');
                upper_right = util_reader.read_color(header_file);
                return true;
            }
            return false;  
        }

        bool verify_lwri_param(ifstream &header_file, string param, rgb &lower_right){
            if (param == LWRI_PARAM){
                util_reader.read_valid_char(header_file, '=');
                lower_right = util_reader.read_color(header_file);
                return true;
            }
            return false;  
        }

        bool verify_min_depht(ifstream &header_file, string param, float &min_depht){
            if (param == MIN_DEPHT){
                util_reader.read_valid_char(header_file, '=');
                header_file >> min_depht;
                return true;
            }
            return false;  
        }
        bool verify_max_depht(ifstream &header_file, string param, float &max_depht){
            if (param == MAX_DEPHT){
                util_reader.read_valid_char(header_file, '=');
                header_file >> max_depht;
                return true;
            }
            return false;  
        }
        bool verify_ray_shots(ifstream &header_file, string param, int &ray_shots){
            if (param == RAY_SHOTS){
                util_reader.read_valid_char(header_file, '=');
                header_file >> ray_shots;
                return true;
            }
            return false;  
        }
        bool verify_threads(ifstream &header_file, string param, int &nthreads){
            if (param == THREADS){
                util_reader.read_valid_char(header_file, '=');
                header_file >> nthreads;
                return true;
            }
            return false;  
        }
        bool verify_natural_light(ifstream &header_file, string param, rgb &natural_light){
            if (param == NATURAL_LIGHT){
                util_reader.read_valid_char(header_file, '=');
                natural_light = util_reader.read_color(header_file);
                return true;
            }
            return false;  
        }
};

#endif