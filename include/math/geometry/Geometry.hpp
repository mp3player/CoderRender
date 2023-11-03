#ifndef _INTERSECTION_TEST_HPP_
#define _INTERSECTION_TEST_HPP_

#include <glm/glm.hpp>


struct Triangle {

    glm::vec3 A;
    glm::vec3 B;
    glm::vec3 C;

};

struct Ray {

    glm::vec3 O;
    glm::vec3 D;

};

struct Plane {

    glm::vec3 P;
    glm::vec3 N;

};

bool isIntersected( const Ray & ray , const Triangle & triangle );

bool isIntersected( const Triangle & ta , const Triangle & tb );

glm::vec3 converToBaryCoordinate( glm::vec3 A , glm::vec3 B , glm::vec3 C , glm::vec3 D );

#endif