#include <core/Log.hpp>


std::ostream & operator << ( std::ostream & cout , glm::mat4 mat ){
    for( int i = 0 ; i < 4 ; ++ i ){
        for( int j = 0 ; j < 4 ; ++ j ){
            std::cout << mat[ j ][ i ] << "\t";
        }
        std::cout << std::endl;
    }
    return cout;
}


std::ostream & operator << ( std::ostream & cout , glm::vec3 vec ){

    std::cout << vec.x << " " << vec.y << " " << vec.z ;
    return cout;

}


std::ostream & operator << ( std::ostream & cout , glm::vec4 vec ){

    std::cout << vec.x << " " << vec.y << " " << vec.z << " " << vec.w ;
    return cout;

}
