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
#include "blinn_phong_shader.h"

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

			switch(header.shader){
				case LAMBERTIAN:
					shader = new LambertianShader(scene);
					break;
				case BLINNPHONG:
					shader = new BlinnPhongShader(scene);
					break;
				case DEPTHCOLOR:
					shader = new DepthColorShader(scene);
					break;
				default:
					shader = new Normals2RGBShader(scene, header);
					break;
			}

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
			// int n_threads = std::thread::hardware_concurrency();
			int n_threads = header.nthreads;

			cout << "Threads Number: " << n_threads << endl;

			vector<thread> block_executions(n_threads);
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

		    return frame;
		}


		/**
		* Aplicando antialiasing
		*
		*/
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

};

#endif