#ifndef _IMG_H_
#define _IMG_H_

#include <vector>
#include <iostream>
#include <math.h>
#include "io/header.h"
#include "vec3.h"
#include "progress_bar.h"

using namespace std;

struct Pixel{
	int r;
	int g;
	int b;
	Pixel(int r_p, int g_p, int b_p) : r(r_p), g(g_p), b(b_p) {}
};

typedef vector< vector<Pixel> > Matrix;
typedef vector<Pixel> Vetor;

class Image{
	public:
		unsigned int width;
		unsigned int height;
		Matrix screen;

		Image(int w, int h){
			width = w;
			height = h;

			// screen = Matrix(h, Vetor(w, Pixel(0,0,0)));
			for(int i = 0; i < h; i++){
				Vetor v;
				for(int j = 0; j < w; j++){
					v.push_back(Pixel(0,0,0));
				}
				screen.push_back(v);
			}

		}

		~Image(){}

		void setPixel(int row, int col, rgb colors){
			screen[row][col].r = int(255.f * colors.r());
            screen[row][col].g = int(255.f * colors.g());
            screen[row][col].b = int(255.f * colors.b());
		}

		void setGammaPixel(int row, int col, rgb colors){
			screen[row][col].r = int(255.f * sqrt(colors.r()));
            screen[row][col].g = int(255.f * sqrt(colors.g()));
            screen[row][col].b = int(255.f * sqrt(colors.b()));
		}

		void print(Header header){

			if(header.type == "PPM"){
				if(header.codi == "ascii"){
					printPPM(header);
				}else if (header.codi == "binary"){
					printPPMBinary(header);
				}
			}
		}

		void printPPMBinary(Header header){

			ofstream output_file(header.name, ofstream::binary);
			char* image_buffer = new char[width*height*3];

		    output_file << "P6" << endl;
		    output_file << width << " " << height << endl;
    		output_file << "255" << endl;

    		progressbar.reset();

    		for(unsigned int i = 0; i < height; i++){
    			for(unsigned int j = 0; j < width; j++){
    				progressbar.increase();

    				image_buffer[((height-i-1)*width*3 + j*3)] 	= screen[i][j].r;
					image_buffer[((height-i-1)*width*3 + j*3 + 1)] = screen[i][j].g;
					image_buffer[((height-i-1)*width*3 + j*3 + 2)] = screen[i][j].b;
    			}
    		}

    		output_file.write(image_buffer, width*height*3);	
  			output_file.close();
			delete [] image_buffer;
		}

		void printPPM(Header header){
			ofstream output_file;
		    output_file.open(header.name);

		    output_file << "P3" << endl;
		    output_file << width << " " << height << endl;
    		output_file << "255" << endl;

    		progressbar.reset();

    		for(int i = height-1; i >= 0; i--){
    			for(unsigned int j = 0; j < width; j++){
    				progressbar.increase();
    				output_file << screen[i][j].r << " " << screen[i][j].g << " " << screen[i][j].b << endl;
    			}
    		}
		}
};

#endif