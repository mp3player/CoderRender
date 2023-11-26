#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <iostream>
#include <glm/glm.hpp>

struct Log {

    template< typename ... Args >
    static void cout( std::string filename , Args ... args );

};

template< typename ... Args >
void Log::cout( std::string filename , Args ... args ){
    
    int index = filename.find_last_of("/");

    filename = filename.substr( index + 1 );
    std::cout <<"[ " << filename << " ] ";
    ( std::cout  << ... << args )  << std::endl;
}


std::ostream & operator << ( std::ostream & cout , glm::mat4 vec );
std::ostream & operator << ( std::ostream & cout , glm::vec3 vec );
std::ostream & operator << ( std::ostream & cout , glm::vec4 vec );


#endif