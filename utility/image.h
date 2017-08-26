#ifndef _IMG_H_
#define _IMG_H_

#include <vector>
#include <iostream>
#include "header.h"
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
			screen[row][col].r = int(255.99f * colors.r());
            screen[row][col].g = int(255.99f * colors.g());
            screen[row][col].b = int(255.99f * colors.b());
		}

		void printPPM(Header header){
			ofstream output_file;
		    output_file.open(header.name);

		    output_file << "P3" << endl;
		    output_file << width << " " << height << endl;
    		output_file << "255" << endl;

    		for(int i = height-1; i >= 0; i--){
    			for(unsigned int j = 0; j < width; j++){
    				progressbar.increase();
    				output_file << screen[i][j].r << " " << screen[i][j].g << " " << screen[i][j].b << endl;
    			}
    		}
		}
};

#endif