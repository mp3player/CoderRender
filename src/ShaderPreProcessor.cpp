#include <opengl/shader/ShaderPreProcessor.hpp>
#include <core/Log.hpp>
#include <core/io/IO.hpp>
#include <sstream>
#include <stack>



const std::string INCLUDE_LIB_FOLDER = "/home/coder/project/c++/engine/shader/lib/";


std::unordered_map< std::string , bool > commands = {
    { "version" , false },
    { "define" , false },
    { "if" , false } ,
    { "endif" , false },
    { "ifdef" , false },
    { "ifndef" , false },
    { "include" , true }
};

/**
 * @brief eliminate space according given mode (0 is just at begining and 1 from the begining to the ending)
 * 
 * @param str 
 * @param mode
 * @return std::string 
 */
std::string trim( std::string str , int mode ){

    int start = 0 , count = -1;
    for( int i = 0 ; i < str.size() ; ++ i ){
        if( str.at(i) != ' ' ) {
            start = i ;
            break;
        }
    }
    if( mode == 1 ){
        for( int i = str.size() - 1 ; i >= 0 ; -- i ){
            if( str.at( i ) == ' ' ){
                count = i - start ;
                break;
            }
        }
    }else{
        count = -1;
    }


    return str.substr( start , count );
}


/**
 * @brief split the line by given char 
 * 
 * @param str 
 * @param chr 
 * @return std::vector< std::string > 
 */
std::vector< std::string > split( std::string str , char chr = ' ' ){
    
    std::vector< std::string > results;

    int index = 0;
    while( index >= 0 ){

        index = str.find_first_of( chr );
        std::string seg = str.substr( 0 , index );

        if( seg.size() > 0 )
            results.push_back( seg );

        str = str.substr( index + 1 , -1 );

    }

    // if( str.size() > 0 )
    //     results.push_back( str );

    return results;

}

/**
 * @brief implementation with string type
 * 
 * @tparam  
 * @param args 
 * @param chr 
 * @return std::string 
 */
template< >
std::string join( std::vector< std::string > args , char chr ){

    std::string result = "";
    for( int i = 0 ; i < args.size() - 1 ; ++ i ){
        result += args.at( i ) + chr;
    }
    result += args.back();
    
    return result ;

}







// preprocessor
ShaderPreProcessor::ShaderPreProcessor( std::string code )
    : sourceCode( code )
{
    // code analysis
    // do preprocess
    this->processedCode = this->parse( this->sourceCode );
    this->analysis( );

}

/**
 * @brief parse include
 * 
 * @param text 
 */
std::string ShaderPreProcessor::parse( std::string text ){

    std::stringstream ss( text );

    std::string line = "";

    std::string processedCode = "";

    while( !ss.eof() ){

        std::getline( ss , line );
        
        if( line.size() <= 0  ) continue;

        if( line.substr( 0 , 2 ) == "\\" ) continue;

        if( line.at( 0 ) == '#' ){
            // xxxxxxx
            std::string indicator = line;
            indicator = trim( indicator.substr( 1 , -1 ) );

            // include<xxxx>
            if( indicator.find( "include" ) != std::string::npos ){
                // <xxxxxxx>

                std::string filename = trim( indicator.substr( std::string( "include" ).size() , -1 ) , 1 );
                filename = filename.substr( 1 , filename.find_last_of('>') - 1 );

                line = this->includeFile( filename );

            }else{
                
            }

        }

        processedCode += line + '\n';

    }

    return processedCode;

}


/**
 * @brief code analysis
 * 
 */
void ShaderPreProcessor::analysis(){

    std::string code = processedCode;

    int index = 0;
    std::stack< std::string > words;

    while( index < code.size() ){
        char chr = code.at( index );

        index += 1;
    }


}

// just process include once
std::string ShaderPreProcessor::includeFile( std::string filename ){

    for( int i = 0 ; i < includeDirectories.size() ; ++ i ){

        std::string directory = includeDirectories.at( i );
        std::string path = directory;

        char last = directory.back();
        if( last  != '\\' & last != '/' ){
            path += '/';
        }

        path += filename + ".glsl";

        std::string code;
        if( readFile( path ,code ) ){
            return "\n// begining of file <" + filename + ">\n" \
            + code + \
            "\n// ending of file <" + filename + ">\n" ;
        }

    }

    return "// can't process include indicator ";

}



