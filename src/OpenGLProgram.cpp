
#include <opengl/shader/OpenGLProgram.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <core/Log.hpp>
#include <core/io/IO.hpp>

// Program


/**
 * @brief Construct a new Program with default shader code
 * 
 */
Program::Program(){

    std::string vPath = "/home/coder/project/c++/engine/shader/basic/vertex.vert",
    fPath = "/home/coder/project/c++/engine/shader/basic/fragment.frag" ;

    std::string vertexCode; ;
    std::string fragmentCode ;

    readFile( vPath , vertexCode );
    readFile( fPath , fragmentCode );

    this->vertexShader = new Shader( vertexCode , GL_VERTEX_SHADER );
    this->fragmentShader = new Shader( fragmentCode , GL_FRAGMENT_SHADER );

}

/**
 * @brief Construct a new Program with given shader code
 * 
 * @param vertexCode 
 * @param fragmentCode 
 */
Program::Program( std::string vertexCode , std::string fragmentCode )
    : vertexShader( new Shader( vertexCode , GL_VERTEX_SHADER ) ),
    fragmentShader( new Shader( fragmentCode , GL_FRAGMENT_SHADER ) )
{
    
}

/**
 * @brief Construct a new Program with given shader
 * 
 * @param vertexShader 
 * @param fragmentShader 
 */
Program::Program( Shader * vertexShader , Shader * fragmentShader ){
    
    this->vertexShader = vertexShader->clone();
    this->fragmentShader = fragmentShader->clone();

}

/**
 * @brief Destroy the Program:: Program object
 * 
 */
Program::~Program(){
    this->dispose();
}

/**
 * @brief compile the program
 * 
 * @return true 
 * @return false 
 */
bool Program::compile(){

    // set commond 
#define Iterator std::unordered_map< std::string , std::string >::iterator


    Iterator begin = this->defines.begin() , end = this->defines.end();

    while( begin != end ){

        std::string key = begin->first;
        std::string value = begin->second;

        begin ++;

        this->fragmentShader->setCommand( key , value );

    }

    this->isValid = this->vertexShader->compile() && this->fragmentShader->compile();
    
    if( !this->isValid ) return false;

    this->UIProgramID = glCreateProgram();

    glAttachShader( this->UIProgramID , this->vertexShader->shaderID );
    glAttachShader( this->UIProgramID , this->fragmentShader->shaderID );

    glLinkProgram( this->UIProgramID );
    int status;
    char info[512];
    glGetProgramiv( this->UIProgramID , GL_LINK_STATUS, &status);

    if (!status) {
        glGetProgramInfoLog( this->UIProgramID , 512, NULL, info);
        Log::cout( __FILE__ , info );
        this->isValid = false;
        return false; 
    }

    this->isValid = true;

    this->regist();

    return this->isValid;

}

/**
 * @brief delete the buffer created in program
 * 
 * @return true 
 * @return false 
 */
void Program::dispose(){

    delete this->vertexShader;
    delete this->fragmentShader;

    if( glIsProgram( this->UIProgramID ) == GL_TRUE ) glDeleteProgram( this->UIProgramID );

    this->isValid = false;

}

/**
 * @brief dispose the program and shader => recreate the program;
 * 
 */
void Program::update(){

    // dispose shader 
    this->vertexShader->dispose();
    this->fragmentShader->dispose();

    if( glIsProgram( this->UIProgramID ) == GL_TRUE ) glDeleteProgram( this->UIProgramID );


    // create new shader and  update program;
    this->compile();

    Log::cout( __FILE__ , "update program" );

}

/**
 * @brief chech wheter the program need to be updated;
 * 
 * @return true 
 * @return false 
 */
bool Program::needUpdate() const {


    return this->vertexShader == nullptr || this->fragmentShader == nullptr || this->vertexShader->needUpdate || this->fragmentShader->needUpdate ;

}

unsigned int Program::ID() const {
    return this->UIProgramID;
}

/**
 * @brief Get the all uniform variables used in this program
 * 
 */
void Program::regist( ){
    
    this->uniforms = std::unordered_map< std::string , int >();
    this->attributes = std::unordered_map< std::string , int >();

    // active uniform 
    int uniformCount = 0;
    glGetProgramiv( this->UIProgramID , GL_ACTIVE_UNIFORMS , &uniformCount );

    int maxLength = 64;
    int length = 0;
    int size = 0;
    GLenum type;
    char name[64];

    for( int i = 0 ; i < uniformCount ; ++ i ){
        glGetActiveUniform( this->UIProgramID , i , maxLength , &length , &size , &type , name );
        this->uniforms.emplace( name , i );
        Log::cout( __FILE__ , "regist : uniform " , name );
    }

    // active attribute
    int attribCount = 0;
    glGetProgramiv( this->UIProgramID , GL_ACTIVE_ATTRIBUTES , &attribCount );

    for( int i = 0 ; i < attribCount ; ++ i ){
        glGetActiveAttrib( this->UIProgramID , i , maxLength , &length , &size , &type , name );
        this->attributes.emplace( name , i );
        Log::cout( __FILE__ , "regist : attribute " , name );
    }

}

/**
 * @brief call glUseProgram 
 * 
 */
void Program::bind(){

    glUseProgram( this->UIProgramID );

}

/**
 * @brief Get the location of a uniform variables by the given name
 * 
 * @param name 
 * @return int 
 */
int Program::getUniformLocation( std::string name ){
    std::unordered_map< std::string , int >::iterator result =  this->uniforms.find( name );
    if( result != this->uniforms.end() ) return this->uniforms.at( name );
    return -1;
}

/**
 * @brief Set the value of a given name
 * 
 * @param name 
 * @param value 
 */
void Program::setUniformValue( std::string name , float value ){
    int location = this->getUniformLocation( name );
    glUniform1f( location , value );
}

void Program::setUniformValue( std::string name , int value ){
    int location = this->getUniformLocation( name );
    glUniform1i( location , value );
}

void Program::setUniformValue( std::string name , bool value ){
    int location = this->getUniformLocation( name );
    glUniform1i( location , value == true ? 1 : -1 );
}

void Program::setUniformValue( std::string name , glm::vec2 value ){
    int location = this->getUniformLocation( name );
    glUniform2fv( location , 1 , glm::value_ptr( value ) );
}

void Program::setUniformValue( std::string name , glm::vec3 value ){
    int location = this->getUniformLocation( name );
    glUniform3fv( location , 1 , glm::value_ptr( value ) );
}

void Program::setUniformValue( std::string name , glm::vec4 value ){
    int location = this->getUniformLocation( name );
    glUniform4fv( location , 1 , glm::value_ptr( value ) );
}

void Program::setUniformValue( std::string name , glm::mat2 value ){
    int location = this->getUniformLocation( name );
    glUniformMatrix2fv( location , 1 , GL_FALSE , glm::value_ptr( value ) );
}

void Program::setUniformValue( std::string name , glm::mat3 value ){
    int location = this->getUniformLocation( name );
    glUniformMatrix3fv( location , 1 , GL_FALSE , glm::value_ptr( value ) );
}

void Program::setUniformValue( std::string name , glm::mat4 value ){
    int location = this->getUniformLocation( name );
    glUniformMatrix4fv( location , 1 , GL_FALSE , glm::value_ptr( value ) );
}

void Program::setDefine( std::string name , std::string value ){

    if( this->defines.find( name ) == this->defines.end() ){
        
        this->defines.emplace( name , value );
    
    }else{

        this->defines.at( name ) = value;

    }

    this->fragmentShader->setCommand( name , value );

}

Program * Program::clone( ){

    Program * _p = new Program( this->vertexShader->shaderCode , this->fragmentShader->shaderCode );

    return _p;

}

/**
 * @brief Create Program Object from the two given file pathes
 * TODO : This object should be destroied automaticly
 * @param vertexPath 
 * @param fragmentPath 
 * @return Program* 
 */
Program * Program::FromFile( std::string vertexPath , std::string fragmentPath ){

    std::string vertexCode ;
    std::string fragmentCode ;
    readFile( vertexPath , vertexCode );
    readFile( fragmentPath , fragmentCode );

    return new Program( vertexCode , fragmentCode );

}
