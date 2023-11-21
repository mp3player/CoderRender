#include <opengl/shader/OpenGLShader.hpp>
#include <core/Log.hpp>
#include <core/io/IO.hpp>
#include <opengl/shader/ShaderPreProcessor.hpp>




bool createShader(const char * const code , unsigned int type , unsigned int & shader){

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code,NULL);
    glCompileShader(shader);
    int status;
    char info[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(shader, 512, NULL, info);
        Log::cout( __FILE__ , type == GL_VERTEX_SHADER ? "VERTEX : " : "FRAGMENT : " , info );
        // Log::cout( __FILE__ , code );
        return false;
    }

    Log::cout( __FILE__ , type == GL_VERTEX_SHADER ? "VERTEX shader" : "FRAGMENT shader " , "successfuly " ) ;
    return true;
}

bool compile( unsigned int & program ){
    
    std::string definedVertexShaderCode ;
    std::string definedFragmentShaderCode;
    readFile("/home/coder/project/c++/opengl/shader/vertex.vert" , definedVertexShaderCode );
    readFile("/home/coder/project/c++/opengl/shader/fragment.frag" , definedFragmentShaderCode );

    program = glCreateProgram();

    unsigned int vertexShader , fragmentShader;
    
    bool vStatus = createShader( definedVertexShaderCode.c_str()   , GL_VERTEX_SHADER   , vertexShader);
    bool fStatus = createShader( definedFragmentShaderCode.c_str() , GL_FRAGMENT_SHADER , fragmentShader);
    
    if (!vStatus || !fStatus) {
        Log::cout( __FILE__ , "create shader failed " );
        return false;
    }
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    int status;
    char info[512];
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(program, 512, NULL, info);
        Log::cout( __FILE__ , info );
        return false;
    }
    //delete the shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}


/**
 * @brief Construct a new Shader:: Shader object
 * 
 * @param code 
 * @param shaderType 
 */
Shader::Shader( std::string shaderCode , GLenum shaderType )
    : shaderCode( shaderCode ),
    shaderType( shaderType )
{
    // combine the config and the code 
    this->isValid = false;
}

/**
 * @brief Destroy the Shader:: Shader object
 * 
 */
Shader::~Shader(){
    this->dispose();
}

/**
 * @brief set the version of the shader
 * 
 * @param version 
 */
void Shader::setVersion( std::string version ){
    
    if( this->version != version ){
        this->version = version;
        this->needUpdate = true;
    }
    

}

/**
 * @brief set the precision used in the shader
 * 
 * @param precision 
 */
void Shader::setPrecision( std::string precision ){

    if( this->precision != precision ){
        this->precision = precision;
        this->needUpdate = true;
    }
    
}

/**
 * @brief get the pre-processed shader coder
 * 
 * @return std::string 
 */
std::string Shader::getPreProcessedShadercode(){


#define Iterator std::unordered_map< std::string , std::string >::iterator

    Iterator begin = this->defines.begin() , end = this->defines.end() ;
    
    std::string shaderDefines = "";

    while( begin != end ){

        shaderDefines += "#define " + begin->first + " " + begin->second + "\n";

        begin ++;

    }

    std::string shaderVersion = "#version " + this->version + "\n";
    std::string shaderPrecision = "precision " + this->precision + " float;\n";
    std::string shaderCode = shaderVersion + shaderPrecision + shaderDefines;

    ShaderPreProcessor processor( this->shaderCode );
    
    
    return shaderCode + processor.processedCode;
    
}

/**
 * @brief compile the shader
 * 
 * @return true 
 * @return false 
 */
bool Shader::compile(){

    std::string code = this->getPreProcessedShadercode();

    this->isValid = createShader( code.c_str() , this->shaderType , this->shaderID );

    this->needUpdate = !this->isValid;

    return this->isValid;

}

/**
 * @brief delete the buffer of the object 
 * 
 * @return true 
 * @return false 
 */
void Shader::dispose(){

    if( glIsShader( this->shaderID ) == GL_TRUE ) glDeleteShader( this->shaderID );
    this->isValid = false;

}

/**
 * @brief delete the shader and recreate it
 * 
 */
void Shader::update(){
    
    this->dispose();
    this->compile();

}

/**
 * @brief set the macro command , such as #define 
 * 
 * @param command 
 * @param arg 
 */
void Shader::setCommand( std::string command , std::string arg ){
    
    if( this->defines.find( command ) == this->defines.end() ) {

        this->defines.emplace( command , arg );

    }else {

        this->defines.at( command ) = arg;

    }

}


Shader * Shader::clone(){
    
    Shader * _shader = new Shader( this->shaderCode , this->shaderType );
    _shader->version = this->version;
    _shader->precision = this->precision;
    
    return _shader;

}

/**
 * @brief Create Shader Object from a file directly
 * 
 * @param path 
 * @param shaderType 
 * @return Shader* 
 */
Shader * Shader::FromFile( std::string path , GLenum shaderType ){

    std::string shaderCode ;
    readFile( path , shaderCode );
    Shader * shader = new Shader( shaderCode , shaderType );
    
    return shader;

}

