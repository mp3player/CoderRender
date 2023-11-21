#ifndef _SHADER_PRE_PROCESSOR_HPP_
#define _SHADER_PRE_PROCESSOR_HPP_

#include <string>
#include <vector>

#include <unordered_map>


std::string trim( std::string str , int mode = 0 );
std::vector< std::string > split( std::string line );

template< typename T >
std::string join( std::vector< T > args , char chr = ' ' );


struct ShaderPreProcessor {

    public:
        std::vector< std::string > includeDirectories = {
            "/home/coder/project/c++/engine/shader/lib/"
        };

    public:
        std::unordered_map< std::string , std::string> defines;
        std::unordered_map< std::string , std::string > parameters;
        std::string sourceCode ;
        std::string processedCode;

    public:
        ShaderPreProcessor( std::string text );

    public:
        std::string parse( std::string );
        void analysis();

    public:
        std::string includeFile( std::string filename );



};


template< typename T >
std::string join( std::vector< T > args , char chr ){

    std::string result = "";
    for( int i = 0 ; i < args.size() - 1 ; ++ i ){
        result += std::to_string( args.at( i ) ) + chr;
    }
    result += std::to_string( args.back() );
    
    return result ;

}



#endif