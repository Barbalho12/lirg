
using namespace utility;

int main(){
	int n_cols(200);
	int n_rows(100);

	std::cout << "p3\n"
			  << n_cols << " " << n_rows << "\n"
			  << "255\n";


	point3 lower_left_corner(-2, -1, -1); // lower left corner of the view plane.
	vec3 horizontal(4, 0, 0); // horizontal dimension of the view plane.
	vec3 vertical(0, 2, 0); //vertical dimension of the view plane.
	point3 origin(0, 0, 0); //the camera origin.

	for(auto row{n_rows-1}; row >= 0; --row){
		for (auto col{0}; col < n_cols; col++){
			auto u = float(col) / float(n_cols);
			auto v = float(row) / float(n_rows);

			//Ray's direction, based on (i,j).
			vec3 ray_dir = (lower_left_corner + u*horizontal + v*vertical) - origin;


			Ray r(origin, ray_dir);


			//Determine the color of the ray, as it travels throgh the virtual space.
			auto c = color(r);

			int ir = int(255.99f * c[rgb::r] )
			int ig = int(255.99f * c[rgb::g] )
			int ib = int(255.99f * c[rgb::b] )

		}
	}


}