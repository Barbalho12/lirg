#ifndef _IMG_H_
#define _IMG_H_

#include <vector>

using namespace std;

typedef struct Pixel{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

typedef vector< vector<Pixel> > Matrix;

class Image{
	public:
		unsigned int width;
		unsigned int height;
		Matrix screen;

		Image(int w, int h){
			width = w;
			height = h;
			screen(w, vector<Pixel>(h, 0));
		}

		~Image(){}
};

#endif