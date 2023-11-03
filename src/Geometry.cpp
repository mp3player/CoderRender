#include <math/geometry/Geometry.hpp>

bool isIntersected( const Ray & ray , const Triangle & triangle ){
    return false;
}

bool isIntersected( const Triangle & ta , const Triangle & tb ){
    return false;
}

glm::vec3 converToBaryCoordinate( glm::vec3 A , glm::vec3 B , glm::vec3 C , glm::vec3 P ){
    
    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;

    glm::vec3 AP = P - A;

    float k1 = glm::dot( AB , AP ) / glm::dot( AB , AB );
    float k2 = glm::dot( AC , AP ) / glm::dot( AC , AC );

    return glm::vec3( 1.0f - k1 - k2 , k1 , k2 );


}
