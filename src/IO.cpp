#include <core/io/IO.hpp>
#include <fstream>
#include <sstream>
#include <core/Log.hpp>

bool readFile( std::string filename , std::string & content ){

    std::fstream f(filename, std::fstream::in);
    std::stringstream ss = std::stringstream();

    if (!f.is_open()) {

        Log::cout( __FILE__ , "filed to read file : " , filename );

        return false ;
    }
    
    ss << f.rdbuf();
    f.close();
    content = ss.str();
    return true;

}