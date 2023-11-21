#ifndef _OPENGL_SHADER_HPP_
#define _OPENGL_SHADER_HPP_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>




struct Shader {

    public:
        GLenum shaderType;
        std::string shaderCode;
        unsigned int shaderID = 0;
        bool isValid = false;
        bool needUpdate = true;

    public:
        std::string version = "450 core";
        std::string precision = "mediump";

    public:

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
        void dispose();
        void update();


        void setCommand( std::string command , std::string args = "" );

    public: 
        Shader * clone();
        
    public:

        static Shader * FromFile( std::string path , GLenum shaderType );

};


#endif