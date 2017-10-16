#include <iostream>
#include <chrono>

#include "../utility/io/reader.h"
#include "../utility/image.h"
#include "../utility/raytracer.h"

using namespace std;

/*
 *  In the near future we'll want to refactor our project to become
 *  something like the code below.
 */
// #ifdef TRADITIONAL_RT
// Image Raytrace (Camera cam, Scene scene, int width, int height)
// {
// 	Image image = new Image (width, height) ;
// 	for (int i = 0 ; i < height ; i++)
// 		for (int j = 0 ; j < width ; j++) {
// 			Ray ray = RayThruPixel (cam, i, j) ;
// 			Intersection hit = Intersect (ray, scene) ;
// 			image[i][j] = FindColor (hit) ;
// 			}
// 	return image ;
// }
// #endif


int main(int argc, char* argv[]){

    cout << "¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨LIRG¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨" << endl;

 	if(argc > 1){

        string file_name = argv[1];

        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

        cout << "Reading Scene from file: " << file_name << endl;
        Reader reader(file_name);

        cout << "Init RayTracer" <<  endl;
        RayTracer raytracer;
        raytracer.init(reader);

        cout << "\nRendering..." << endl;
        Image image = raytracer.ray_trace();

        cout << "\nSaving in file: " << reader.name << endl;
        image.print(reader);

        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = t2 - t1;
        cout << "\nRendering time: " << duration.count() << " seconds." << endl;

    }else{
        cout << "No scene entered" << endl;
    }

    cout << "¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨"  << endl;
}
