#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <opengl/shader/OpenGLShader.hpp>

// lazy compiling
// check out whether the material 


// bool createShader(const char * const code , unsigned int type , unsigned int & shader);

// bool createProgram( const char * const vCode , const char * const fCode , unsigned int & program );

// bool compile( unsigned int & program );





struct Program  {

    public:
        std::unordered_map< std::string , int > uniforms;
        std::unordered_map< std::string , int > attributes;
        std::unordered_map< std::string , std::string > defines;

        Shader * vertexShader = nullptr ;
        Shader * fragmentShader = nullptr ;

        unsigned int UIProgramID = 0;

        bool isValid = false;
        

    public:
        Program();
        Program( std::string vertexCode , std::string fragmentCode );
        Program( Shader * vertexShader , Shader * fragmentShader );
        ~Program(); 

    public:
        bool compile();
        void dispose();
        void update();

        bool needUpdate() const ;
        unsigned int ID() const ;

    public:

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

    public:
        Program * clone();

    public:

        static Program * FromFile( std::string vertexPath , std::string fragmentPath );

};




#endif 