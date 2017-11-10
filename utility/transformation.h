#ifndef _TRANS_H_
#define _TRANS_H_

#include <ios>      // std::left
#include <iomanip> // setw
#include <vector>
#include <iostream>

// vec3, vec4, ivec4, mat4
#include <glm/glm.hpp>
// translate, rotate, scale, perspective
#include <glm/gtc/matrix_transform.hpp>

#include "object.h"
#include "vec3.h"

using namespace std;

/// Prints a column-major 4x4 matriz.
std::ostream & operator<<( std::ostream& os, const glm::mat4& m )
{
    for (auto i(0) ; i < 4 ; ++i )
    {
        os << "[ ";
        for ( auto j(0) ; j < 4 ; ++j )
            os << std::fixed << std::right << std::setw(6) << std::setprecision(2) << m[j][i] << " ";
        os << "]\n";
    }

    return os;
}

/// Prints a 3D vector.
std::ostream & operator<<( std::ostream& os, const glm::vec3& v )
{
        os << "[ ";
        for ( auto j(0) ; j < 3 ; ++j )
            os << std::right << std::setw(6) << std::setprecision(2) << v[j] << " ";
        os << "]";

    return os;
}

/// Prints a 4D vector.
std::ostream & operator<<( std::ostream& os, const glm::vec4& v )
{
        os << "[ ";
        for ( auto j(0) ; j < 4 ; ++j )
            os << std::right << std::setw(6) << std::setprecision(2) << v[j] << " ";
        os << "]";

    return os;
}

constexpr long double operator"" _deg ( long double deg ){
	return deg*3.141592/180;
}

class Transformation{
	private:
		glm::vec4 toVec4Glm(point3 p){
			return glm::vec4(p.x(), p.y(), p.z(),1);
		}

		point3 toPoint3(glm::vec4 v){
			return point3(v[0], v[1], v[2]);
		}

	public:
		Transformation(){
		}

		void rotation(Object *obj, point3 rotatePoint, float x, float y, float z){
            
            printf("[%lf,%lf,%lf]\n", obj->getPoints()[0]->x(), obj->getPoints()[0]->y(), obj->getPoints()[0]->z());
            
            point3 p = rotatePoint;// (obj->getPoints()[rotatePoint]->x(), obj->getPoints()[rotatePoint]->y(), obj->getPoints()[rotatePoint]->z());
            translation(obj, -p.x(), -p.y(), -p.z());
            //translation(obj, -obj->getPoints()[rotatePoint]->x(), -obj->getPoints()[rotatePoint]->y(), -obj->getPoints()[rotatePoint]->z());

            printf("[%lf,%lf,%lf]\n", obj->getPoints()[0]->x(), obj->getPoints()[0]->y(), obj->getPoints()[0]->z());

            glm::mat4 Model = glm::mat4(1.0f);
            Model = glm::rotate(Model, (float)(x*3.141592/180), glm::vec3(1, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
            Model = glm::rotate(Model, (float)(y*3.141592/180), glm::vec3(0, 1, 0));
            Model = glm::rotate(Model, (float)(z*3.141592/180), glm::vec3(0, 0, 1));
            auto Rotate = Model;

            for(unsigned int i = 0; i < obj->getPoints().size(); i++){
                auto newPoint = Rotate * toVec4Glm(*obj->getPoints()[i]);
                *obj->getPoints()[i] = toPoint3(newPoint);
            }

            translation(obj, p.x(), p.y(), p.z());

            printf("[%lf,%lf,%lf]\n", obj->getPoints()[0]->x(), obj->getPoints()[0]->y(), obj->getPoints()[0]->z());
		}

		void translation(Object *obj, float x, float y, float z){
			glm::vec3 translate(x, y, z);
			glm::mat4 Take2Start = glm::translate(glm::mat4(1.0f), translate);
    		auto Translate = Take2Start;

    		for(unsigned int i = 0; i < obj->getPoints().size(); i++){
				auto newPoint = Translate * toVec4Glm(*obj->getPoints()[i]);
				*obj->getPoints()[i] = toPoint3(newPoint);
    		}

    		// cout << *obj->getPoints()[0] << endl;
		}

		// scalation(){

		// }
};

#endif