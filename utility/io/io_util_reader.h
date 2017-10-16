#ifndef _IO_UTIL_READER_H_
#define _IO_UTIL_READER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../vec3.h"
#include "../ray.h"

using namespace std;


class IoUtilReader{

    public:

        IoUtilReader(){}

        /**
        * Ler e valida um caractere, se não válido, o programa é finalizado
        */
        void read_valid_char(ifstream &header_file, char expected_char){
            char character;
            header_file >> character; 
            if(character != expected_char){
                cout << "ERRO: no expected character: '"<< character <<"',  expected: '" << expected_char << "'" << endl;
                exit (EXIT_FAILURE);
            }
        }

        /**
        * Ler e valida uma string, se não válida, o programa é finalizado
        */
        void read_valid_string(ifstream &header_file, string expected_string){
            string text;
            header_file >> text; 
            if(text != expected_string){
                cout << "ERRO: no expected string: '"<< text <<"',  expected: '" << expected_string << "'" << endl;
                exit (EXIT_FAILURE);
            }

        }

        /**
        * Valida uma string, se não válida, o programa é finalizado
        */
        void validate_string(string text, string expected_string){
            if(text != expected_string){
                cout << "ERRO: no expected string: '"<< text <<"',  expected: '" << expected_string << "'" << endl;
                exit (EXIT_FAILURE);
            }

        }

        /**
        * Ler uma lista de cores
        * EXAMPLE: {RGB 255 255 255 RGB 255 255 255 URGB 1.0 1.0 1.0}
        */
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

        /**
        * Ler um vetor 
        * EXAMPLE: 1.0 0.5 0.0
        * EXAMPLE: 255 177 0
        */
        vec3 read_vec3(ifstream &header_file){
            float a,b,c;
            header_file >> a;
            header_file >> b;
            header_file >> c;
            return vec3(a,b,c);
        }

        /**
        * Ler uma cor, 
        * (RGB) 0 ~ 255 
        * (URGB) 0.0 ~ 1.0
        */
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
};

#endif