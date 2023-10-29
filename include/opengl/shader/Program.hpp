#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

// lazy compiling
// check out whether the material 


// bool createShader(const char * const code , unsigned int type , unsigned int & shader);

// bool createProgram( const char * const vCode , const char * const fCode , unsigned int & program );

// bool compile( unsigned int & program );

static std::string trim( std::string str , int mode = 0 );
static std::vector< std::string > parseCommand( std::string line );
static std::string readFile( std::string fileName );
static std::string execCommand( std::vector< std::string > commands );

struct Shader {

    public:
        GLenum shaderType;
        std::string shaderCode;
        unsigned int shaderID = 0;
        bool isReady;
        std::string version = "450 core";
        std::string precision = "mediump";

        std::unordered_map< std::string , std::string > defines;
    
    public:
        Shader( std::string shaderCode , GLenum shaderType );
        ~Shader();

    public:
        void setVersion( std::string version );
        void setPrecision( std::string precision );

        std::string getPreProcessedShadercode();

    public:
        bool compile();
        bool dispose();

        void setCommand( std::string command , std::string args = "" );
    public:

        static Shader * FromFile( std::string path , GLenum shaderType );

};

struct Program  {

    public:
        std::unordered_map< std::string , int > uniforms;
        std::unordered_map< std::string , int > attributes;
        std::unordered_map< std::string , std::string > defines;

        Shader * vertexShader = nullptr ;
        Shader * fragmentShader = nullptr ;

        unsigned int programID = 0;
        bool isReady;

    public:
        Program( std::string vertexCode , std::string fragmentCode );
        ~Program(); 

    public:
        bool compile();
        bool dispose();


        void bind();
        
    public:
        void regist();
        int getUniformLocation( std::string name );

        void setUniformValue( std::string name , float value );
        void setUniformValue( std::string name , int value );
        void setUniformValue( std::string name , bool value );
        void setUniformValue( std::string name , glm::vec2 value );
        void setUniformValue( std::string name , glm::vec3 value );
        void setUniformValue( std::string name , glm::vec4 value );
        void setUniformValue( std::string name , glm::mat2 value );
        void setUniformValue( std::string name , glm::mat3 value );
        void setUniformValue( std::string name , glm::mat4 value );

        void setDefine( std::string name , std::string value = "" );

        static Program * FromFile( std::string vertexPath , std::string fragmentPath );

};




#endif 