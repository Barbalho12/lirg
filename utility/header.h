#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include "vec3.h"

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

        void print(){
            cout << name << endl;
            cout << type << endl;
            cout << codi << endl;
            cout << width << endl;
            cout << height << endl;
            cout << "(" << upper_left.r() << ", " << upper_left.g() << ", " << upper_left.b() << ")" << endl;
            cout << "(" << lower_left.r() << ", " << lower_left.g() << ", " << lower_left.b() << ")" << endl;
            cout << "(" << upper_right.r() << ", " << upper_right.g() << ", " << upper_right.b() << ")" << endl;
            cout << "(" << lower_right.r() << ", " << lower_right.g() << ", " << lower_right.b() << ")" << endl;
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
                        upper_left = read_rgb(header_file);
                    }

                    if(text == LWLF_PARAM){
                        header_file >> text;
                        lower_left = read_rgb(header_file);
                    }

                    if(text == UPRI_PARAM){
                        header_file >> text;
                        upper_right = read_rgb(header_file);
                    }

                    if(text == LWRI_PARAM){
                        header_file >> text;
                        lower_right = read_rgb(header_file);
                    }
                }
            }else{
                cout << "file is not open" << endl;
            }

            header_file.close();
        }

        rgb read_rgb(ifstream &header_file){
            int r,g,b;
            header_file >> r;
            header_file >> g;
            header_file >> b;
            return rgb(r,g,b);
        }

};

#endif