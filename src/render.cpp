#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <ratio>
#include <chrono>
#include "../utility/vec3.h"
#include "../utility/ray.h"
#include "../utility/sphere.h"
#include "../utility/camera.h"
#include "../utility/header.h"
#include "../utility/image.h"

// using namespace std::chrono;
using namespace utility;
using namespace std;

random_device randomizer;
mt19937 gen(randomizer());

Header header;

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

float hit_sphere(Sphere s, Ray r){
    float a = dot(r.get_direction(), r.get_direction());
    float b = dot(((r.get_origin() - s.get_center())), r.get_direction());
    float c = dot(((r.get_origin() - s.get_center())), ((r.get_origin() - s.get_center()))) - (s.get_radius() * s.get_radius());

    // float t1 = (-b + sqrt(dot(b, b) - (dot(a,c))))/a;
    float t2 = (-b - sqrt(dot(b, b) - (dot(a,c))))/a;

    return t2;
}

rgb make_background_point(const Ray &r_){
    rgb top_left = header.upper_left/255.99f;
    rgb bottom_left = header.lower_left/255.99f;
    rgb top_right = header.upper_right/255.99f;
    rgb bottom_right = header.lower_right/255.99f;

    float t = 0.5 * r_.get_direction().y() + 0.5;
    float u = 0.25 * r_.get_direction().x() + 0.5;

    rgb result = bottom_left*(1-t)*(1-u) + 
                 top_left*t*(1-u) + 
                 bottom_right*u*(1-t) + 
                 top_right*t*u;

    return result;
}

rgb make_background_default(const Ray &r_, float t, point3 center, float min_depht, float max_depht){
    if( t >= min_depht && t < max_depht){
        point3 p = r_.point_at(t);
        vec3 v = unit_vector(p - center);

        return rgb( (v.x()+1)/2.0,
                   (v.y()+1)/2.0,
                   (v.z()+1)/2.0);
    }else{
        return make_background_point(r_);
    }
}


rgb make_foreground_to_background_depth(float t, float min_depht, float max_depht){
    rgb depth_foreground = rgb(0, 0, 0);
    rgb depth_background = rgb(1, 1, 1);

    rgb cor;

    if (t >= min_depht && t <= max_depht) {
        t = t/max_depht;
        cor = ((1-t) * depth_foreground) + (t*depth_background);
    }else{
        cor = depth_background;
    }
    return cor;
}

Sphere hitSpheres(float min_depht, float max_depht, const Ray &r_, vector<Sphere> spheres, float &t){
    t = max_depht; 
    Sphere s; 
    for(unsigned int i = 0; i < spheres.size(); i++){
        float t_aux = hit_sphere(spheres[i], r_);
        if(t > t_aux && t_aux > min_depht){
            t = t_aux;
            s = spheres[i];
        }
    }
    return s;
 }


rgb color(const Ray &r_){

    // float min_depht = 0;
    // float max_depht = 3;
    float min_depht = header.min_depht;
    float max_depht = header.max_depht;
    // cout << min_depht << "," << max_depht << endl;

    vector<Sphere> spheres;

    spheres.push_back(Sphere( point3(0,-100.5,-3), 99.f));
    spheres.push_back(Sphere( point3( 0.3 , 0 , -1 ),0.4));
    spheres.push_back(Sphere( point3( 0 , 1 , -2 ),0.6));
    spheres.push_back(Sphere( point3(-0.4 , 0 , -3 ),0.7));

    float t; 

    Sphere s = hitSpheres(min_depht, max_depht, r_, spheres, t);

    if(header.depth_mode){
        return make_foreground_to_background_depth(t, min_depht, max_depht);
    }else{
        return make_background_default(r_, t, s.get_center(), min_depht, max_depht);
    }
    // return make_foreground_to_background_depth(t, min_depht, max_depht);

    

}

// rgb colorDefaut(int col, int row, int n_cols, int n_rows, Camera &camera){
//     float u = float(col) / float(n_cols); // walked u% of the horizontal dimension of the view plane.
//     float v = float(row) / float(n_rows); // walked v% of the vertical dimension of the view plane.

//     point3 end_point = camera.lower_left_corner + u*camera.h_axis + v*camera.v_axis ;
//     Ray r(camera.origin, end_point - camera.origin);

//     return color(r);
// }

rgb colorSoftened(int col, int row, int n_cols, int n_rows, Camera &camera){
    rgb c;
    float u, v;

    for (int i = 0; i < header.ray_shots; i++){

        u = float(col + generate_canonical<double, 10>(gen)) / float(n_cols);
        v = float(row + generate_canonical<double, 10>(gen)) / float(n_rows);

        point3 end_point = camera.lower_left_corner + u*camera.h_axis + v*camera.v_axis ;
        Ray r(camera.origin, end_point - camera.origin);

        c += color(r);
    }

    return c / header.ray_shots;
}

int makeImage(){
    // int n_samples = 100; // Number of ray shots on a pixel

    // ofstream output_file;
    // output_file.open(header.name);

    // output_file << "P3" << endl;
    // output_file << header.width << " " << header.height << endl;
    // output_file << "255" << endl;

    Image frame(header.width, header.height);


    point3 lower_left_corner(-2, -1, -1); // lower left corner of the view plane.
    vec3 horizontal(4, 0, 0); // Horizontal dimension of the view plane.
    vec3 vertical(0, 2, 0); // Vertical dimension of the view plane.
    point3 origin(0, 0, 0); // the camera's origin.

    Camera camera(lower_left_corner, vertical, horizontal, origin);

    // Y
    for (int row = header.height-1; row >= 0; --row){

        // X
        for(int col = 0; col < header.width; col++){

            rgb colors = colorSoftened(col, row, header.width, header.height, camera);
            // rgb c = colorDefaut(col, row, header.width, header.height, camera);

            frame.setPixel(row, col, colors);
            // int r = int(255.99f * c.r());
            // int g = int(255.99f * c.g());
            // int b = int(255.99f * c.b());

            // output_file << r << " " << g << " " << b << endl;
        }
    }

    frame.printPPM(header);
    return 0;
}

int main(int argc, char* argv[]){

 	if(argc > 1){

        string file_name = argv[1];
        
        cout << "Reading Scene " << file_name << endl;

        header = Header(file_name);

        cout << "Rendering in " << header.name << endl;

        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

        makeImage();

        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = t2 - t1;
        cout << "Rendering time: " << duration.count() << " seconds." << endl;


    }else{
        cout << "No scene entered" << endl;
    }
}
