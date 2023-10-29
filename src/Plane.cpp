#include <math/plane.hpp>

Plane::Plane( float A , float B , float C , float D )
    : A( A ) , 
        B( B ) ,
        C( C ),
        D( D ),
        normal( A , B, C )
    {}

Plane Plane::fromPointAndNormal( glm::vec3 point , glm::vec3 normal ){
    
    float A = normal.x ;
    float B = normal.y ;
    float C = normal.z ;
    float D = glm::dot( point , normal );

    return Plane( A , B , C , D );
}

// the plane is an affine set of {p0,p1,p2}
static Plane fromPoint( glm::vec3 p0 , glm::vec3 p1 , glm::vec3 p2 ){
    glm::vec3 v0 = p1 - p0;
    glm::vec3 v1 = p2 - p1;
    glm::vec3 normal = glm::cross( v0 , v1 );

    return Plane::fromPointAndNormal( p0 , normal );
}

