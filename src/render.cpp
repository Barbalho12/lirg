#include <iostream>
#include <vector>
#include "../utility/vec3.h"
#include "../utility/ray.h"
#include "../utility/sphere.h"

using namespace utility;
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

float hit_sphere(Sphere s, Ray r){
    float a = dot(r.get_direction(), r.get_direction());
    float b = dot(((r.get_origin() - s.get_center())), r.get_direction());
    float c = dot(((r.get_origin() - s.get_center())), ((r.get_origin() - s.get_center()))) - (s.get_radius() * s.get_radius());

    float t1 = (-b + sqrt(dot(b, b) - (dot(a,c))))/a;
    float t2 = (-b - sqrt(dot(b, b) - (dot(a,c))))/a;

    return t2;
}

rgb make_background_point(const Ray &r_){
    rgb top_left (0.5,0.7,1);
    rgb bottom_left(1,1,1);
    rgb top_right (0.5,0.7,1);
    rgb bottom_right (1,1,1);
    
    float t = 0.5 * r_.get_direction().y() + 0.5;
    float u = 0.25 * r_.get_direction().x() + 0.5;

    rgb result = bottom_left*(1-t)*(1-u) + 
                 top_left*t*(1-u) + 
                 bottom_right*u*(1-t) + 
                 top_right*t*u;

    return result;
}

rgb color(const Ray &r_){

    vector<Sphere> spheres;

    // point3 sphere_center = point3(0, 0, -1);
    Sphere s1 = Sphere( point3(0,-100.5,-3), 99.f);
    Sphere s2 = Sphere( point3( 0.3 , 0 , -1 ),0.4);
    Sphere s3 = Sphere( point3( 0 , 1 , -2 ),0.6);
    Sphere s4 = Sphere( point3(-0.4 , 0 , -3 ),0.7);

    spheres.push_back(s1);
    spheres.push_back(s2);
    spheres.push_back(s3);
    spheres.push_back(s4);

    rgb cor;

    point3 center;

    float t = 1001; 

    for(int i = 0; i < spheres.size(); i++){
        float t_aux = hit_sphere(spheres[i], r_);
        if(t > t_aux && t_aux > -1){
            t = t_aux;
            center = spheres[i].get_center();

        }
    }

    //-1 é a posição da câmera e 1000 é o limite de profundidade
    if( t > -1 && t <= 1000){
        point3 p = r_.point_at(t);
        vec3 v = unit_vector(p - center);

        cor = rgb( (v.x()+1)/2.0,
                   (v.y()+1)/2.0,
                   (v.z()+1)/2.0);
        return cor;
    }else{
        return make_background_point(r_);
    }
}

int makeImage(){
    int n_cols = 1200;
    int n_rows = 600;

    std::cout << "P3\n"
              << n_cols << " " << n_rows << "\n"
              << "255\n";

    //=== Defining our 'camera'
    point3 lower_left_corner(-2, -1, -1); // lower left corner of the view plane.
    vec3 horizontal(4, 0, 0); // Horizontal dimension of the view plane.
    vec3 vertical(0, 2, 0); // Vertical dimension of the view plane.
    point3 origin(0, 0, 0); // the camera's origin.

    // NOTICE: We loop rows from bottom to top.
    // Y
    for (int row = n_rows-1; row >= 0; --row){

        // X
        for(int col = 0; col < n_cols; col++){

            // Determine how much we have 'walked' on the image: in [0,1]
            float u = float(col) / float(n_cols); // walked u% of the horizontal dimension of the view plane.
            float v = float(row) / float(n_rows); // walked v% of the vertical dimension of the view plane.

            point3 end_point = lower_left_corner + u*horizontal + v*vertical ;
            
            // The ray:
            Ray r(origin, end_point - origin);

            // Determine the color of the ray, as it travels through the virtual space.
            rgb c = color(r);

            int ir = int(255.99f * c.r());
            int ig = int(255.99f * c.g());
            int ib = int(255.99f * c.b());

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

    return 0;
}

int main(/*int argc, char* argv[]*/){

    // int x = 0;
    // int y = 0;
    // if(argc > 1){
    //     x = atoi(argv[1]);
    // }
    // if(argc > 2){
    //     y = atoi(argv[2]);
    // }

    makeImage();
}
