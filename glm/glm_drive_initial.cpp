#include <iostream> // ostream
#include <ios>      // std::left
#include <iomanip> // setw

// vec3, vec4, ivec4, mat4
#include <glm/glm.hpp>
// translate, rotate, scale, perspective
#include <glm/gtc/matrix_transform.hpp>


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


/// User-define literal to convert from degrees to radian.
constexpr long double operator"" _deg ( long double deg )
{
    return deg*3.141592/180;
}

int main( void )
{
    // The rotation angles for each axis.
    glm::vec3 rotate( 45.0_deg, 30.0_deg, 60.0_deg ); 

    // The triangle's vertices.
    glm::vec4 p1( 2, 4, 0, 1 );
    glm::vec4 p2( 5, 3, 0, 1 );
    glm::vec4 p3( 5, 5, 0, 1 );

    std::cout << ">>> Original vertices are: " << p1 << ", " << p2 << ", " << p3 << std::endl;

    // (1) Translate the points back from the origin to the original pivot position.
    //glm::vec3 translate(2, 4, 0); // Translation factor.
    glm::vec3 translate(-2, -4, 0); // Translation factor.
    glm::mat4 Take2Start = glm::translate(
            glm::mat4(1.0f), // Identity.
            translate);
    auto Translate = Take2Start;
    std::cout << "Translate by " << translate << " : \n";
    std::cout << Translate << std::endl;


    return 0;
}
