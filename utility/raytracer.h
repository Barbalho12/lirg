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
#include "io/reader.h"
#include "image.h"
#include "progress_bar.h"
#include "scene.h"
#include "shader.h"
#include "lambertian_shader.h"
#include "depth_color_shader.h"
#include "normals2rgb_shader.h"
#include "blinn_phong_shader.h"
#include "toon_shader.h"
#include "light.h"
#include "background.h"
#include "bp_lambertian_shader.h"
#include "transformation.h"
#include "box.h"

using namespace std::chrono;
using namespace utility;
using namespace std;

random_device randomizer;
mt19937 gen(randomizer());


class RayTracer{

	private: 

		Camera *camera;
		Scene scene;
		int width;
		int height;

		Reader reader;

		Shader *shader;

		Transformation transformation;

	public:
		RayTracer(){
		}

		//Dá entrada dos dados
		void init(Reader reader_){

			reader = reader_;

			width = reader_.width;
			height = reader_.height;

			progressbar.setDimension(width*height);

			// vec3 lookfrom(3,3,2);
			//vec3 lookat(0,0,-1);
			// float dist_to_focus = (lookfrom-vec3(-1,0,-1)).length();
			// float aperture = 2.0;

			// camera = Camera(lookfrom, lookat, vec3(0,1,0), 20, float(width)/float(height), aperture, dist_to_focus);
			camera = reader_.camera;

			// camera = Camera(
			// 	vec3(-2,2,1),
			// 	vec3(0,0,-1),
			// 	vec3(0,1,0),
			// 	90,
			// 	float(width)/float(height));
			// camera = Camera(reader.lower_left_corner, // lower left corner of the view plane.
			// 	reader.v_d_view_plane,  // Vertical dimension of the view plane.
			// 	reader.h_d_view_plane,  // Horizontal dimension of the view plane.
			// 	reader.camera_origin);	// the camera's origin.

			scene = Scene();

			scene.setObjects(reader.objects);

			// scene.addObject(new Box(point3(1,1,1), point3(-1,-1,-1), new Lambertian(rgb(1,0,0))));

			transformation = Transformation();
			transformation.scalation(scene.getObject(scene.getObjects().size()-4), 0.5);
			// transformation.translation(scene.getObject(3), 0, -0.1, 0);
			// transformation.translation(scene.getObject(scene.getObjects().size()-3), 1, 0, 0);
			// transformation.scalation(scene.getObject(0), 2, 2, 2);
			// transformation.rotation(scene.getObject(3), *scene.getObject(0)->getPoints()[0], 0.0, 15.0, 0.0);
			scene.setLights(reader.lights);
			scene.setNaturalLight(reader.natural_light);
			scene.setMaxDepht(reader.max_depht);
			scene.setMinDepht(reader.min_depht);
			scene.background = Background(reader.upper_left, reader.lower_left, reader.upper_right, reader.lower_right);

			switch(reader.shader){
				case LAMBERTIAN:
					shader = new LambertianShader(scene);
					break;
				case BLINNPHONG:
					shader = new BlinnPhongShader(scene);
					break;
				case DEPTHCOLOR:
					shader = new DepthColorShader(scene, reader.d_foreground_color, reader.d_background_color);
					break;
				case BP_LAMBERTIAN:
					shader = new BP_LambertianShader(scene);
					break;
				case TOON:
					shader = new ToonShader(scene);
					break;
				default:
					shader = new Normals2RGBShader(scene);
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
			int n_threads = reader.nthreads;

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

		    for (int i = 0; i < reader.ray_shots; i++){

		        u = float(col + generate_canonical<double, 10>(gen)) / float(width);
		        v = float(row + generate_canonical<double, 10>(gen)) / float(height);

		        Ray r = camera->getRay(u, v);
		        // point3 end_point = camera.lower_left_corner + u*camera.h_axis + v*camera.v_axis ;
		        // Ray r(camera.origin, end_point - camera.origin);

		        c += shader->color(r);
		    }

		    return c / reader.ray_shots;
		}

};

#endif