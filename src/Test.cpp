#include <math/test.hpp>


bool test( const Plane & plane , glm::vec3 point ){
    float x = -plane.D / plane.A;
    glm::vec3 vec = point - glm::vec3( x , 0 , 0 );

    return glm::dot( vec , plane.normal ) > 0 ? true : false;
}

bool test( const Ray & ray , const Triangle & triangle ){

}