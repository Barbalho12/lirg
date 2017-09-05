#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include "vec3.h"
#include "ray.h"
#include "object.h"
#include "sphere.h"
#include "camera.h"
#include "header.h"
#include "image.h"
#include "progress_bar.h"
#include "scene.h"
#include "shader.h"
#include "lambertian_shader.h"
#include "depth_color_shader.h"
#include "normals2rgb_shader.h"

using namespace std::chrono;
using namespace utility;
using namespace std;

random_device randomizer;
mt19937 gen(randomizer());

class RayTracer{

	private: 

		Camera camera;
		Scene scene;
		// ResourceManager materials;
		int width;
		int height;

		Header header;

		Shader *shader;

	public:
		RayTracer(){
		}

		//Dá entrada dos dados
		void init(Header header_){

			header = header_;

			width = header_.width;
			height = header_.height;

			progressbar.setDimension(width*height);

			camera = Camera(header.lower_left_corner, // lower left corner of the view plane.
				header.v_d_view_plane,  // Vertical dimension of the view plane.
				header.h_d_view_plane,  // Horizontal dimension of the view plane.
				header.camera_origin);	// the camera's origin.

			scene = Scene();

			scene.setObjects(header.objects);
			scene.setMaxDepht(header.max_depht);
			scene.setMinDepht(header.min_depht);

			 shader = new LambertianShader(scene);
			 //shader = new DepthColorShader(scene);
			//shader = new Normals2RGBShader(scene, header);

		}
		
		void pixel_solve(Image &frame, int width, int height_top, int height_bottom){
			for (int row = height_top; row >= height_bottom; --row){
		    for(int col = 0; col < width; col++){
		        rgb colors = colorSoftened(col, row);
		        frame.setGammaPixel(row, col, colors);

		        progressbar.increase();
		    }
		}
		}
		
		Image ray_trace(){

			Image frame(width, height);

			//Define numero de threads
			//int n_threads = 4;
			int n_threads = std::thread::hardware_concurrency();

			cout << "Threads Number: " << n_threads << endl;

			vector<thread> block_executions(n_threads);

			//thread block_executions[8];
			int n = 1;
			while ( n <= n_threads){
				int height_top =  (height*(n*1.0/n_threads))-1;
				int height_bottom = height*((n-1)*1.0/n_threads);
				block_executions[n-1] = thread(&RayTracer::pixel_solve, this, std::ref(frame), width, height_top, height_bottom);
		    	n++;
			}

			for (int i=0; i < n_threads; i++){
		        block_executions[i].join();
		    }

		    // for (int row = height-1; row >= 0; --row){
		    //     for(int col = 0; col < width; col++){
		    //         rgb colors = colorSoftened(col, row);
		    //         frame.setGammaPixel(row, col, colors);
		    //         progressbar.increase();
		    //     }
		    // }

		    return frame;
		}

		// rgb color(const Ray &r, int depth){

		//     HitRecord ht;
		//     ht.t = header.max_depht;


		//     // hit_anything(scene.getObjects(), ht, r);

		//     if(hit_anything(scene.getObjects(), ht, r)){

		//     	Ray scattered;
		//     	vec3 attenuation;
		//     	if(depth < header.max_depht && ht.material->scatter(r, ht, attenuation, scattered)){
		//     		return attenuation*color(scattered, depth+1);
		//     		// return vec3(0,1,0);
		//     	}else{
		//     		return vec3(0,0,0);
		//     	}
		//     	// vec3 target = ht.origin + ht.normal + random_in_unit_sphere();
		//     	// return 0.5*color( Ray(ht.origin, target-ht.origin),0);
		//     }else{
		//     	// vec3 unit_direction = unit_vector(r.get_direction());
		//     	// float t = 0.5*(unit_direction.y()*1.0);
		//     	// return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
		//     	if(header.depth_mode){
		//         	return make_foreground_to_background_depth(ht, header.min_depht, header.max_depht);
		//     	}else{
		//         	return make_background_default(r, ht, header.min_depht, header.max_depht);
		//     	}
		//     }
		// }

		rgb colorSoftened(int col, int row){
		    rgb c;
		    float u, v;

		    for (int i = 0; i < header.ray_shots; i++){

		        u = float(col + generate_canonical<double, 10>(gen)) / float(width);
		        v = float(row + generate_canonical<double, 10>(gen)) / float(height);

		        point3 end_point = camera.lower_left_corner + u*camera.h_axis + v*camera.v_axis ;
		        Ray r(camera.origin, end_point - camera.origin);

		        c += shader->color(r);
		    }

		    return c / header.ray_shots;
		}


		// rgb make_background_point(const Ray &r_){
		//     rgb top_left = header.upper_left/255.99f;
		//     rgb bottom_left = header.lower_left/255.99f;
		//     rgb top_right = header.upper_right/255.99f;
		//     rgb bottom_right = header.lower_right/255.99f;

		//     float t = 0.5 * r_.get_direction().y() + 0.5;
		//     float u = 0.25 * r_.get_direction().x() + 0.5;

		//     rgb result = bottom_left*(1-t)*(1-u) + 
		//                  top_left*t*(1-u) + 
		//                  bottom_right*u*(1-t) + 
		//                  top_right*t*u;

		//     return result;
		// }

		// rgb make_background_default(const Ray &r_, HitRecord ht, float min_depht, float max_depht){
		//     if( ht.t >= min_depht && ht.t < max_depht){
		//         point3 p = r_.point_at(ht.t);
		//         vec3 v = unit_vector(p - ht.origin);

		//         return rgb((v.x()+1)/2.0,
		//                    (v.y()+1)/2.0,
		//                    (v.z()+1)/2.0);
		//     }else{
		//         return make_background_point(r_);
		//     }
		// }

		// rgb make_foreground_to_background_depth(HitRecord ht, float min_depht, float max_depht){
		//     rgb depth_foreground = rgb(0, 0, 0);
		//     rgb depth_background = rgb(1, 1, 1);

		//     rgb cor;

		//     if (ht.t >= min_depht && ht.t <= max_depht) {
		//         ht.t = ht.t/max_depht;
		//         cor = ((1-ht.t) * depth_foreground) + (ht.t*depth_background);
		//     }else{
		//         cor = depth_background;
		//     }
		//     return cor;
		// }


};

#endif