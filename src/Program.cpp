
#include <opengl/shader/Program.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <core/Log.hpp>

const std::string INCLUDE_LIB_FOLDER = "/home/coder/project/c++/engine/shader/lib/";

static std::string readFile( std::string fileName){
    std::fstream f(fileName, std::fstream::in);
    std::stringstream ss = std::stringstream();

    if (!f.is_open()) {

        Log::cout( __FILE__ , "filed to read file : " , fileName );

        return "";
    }
    ss << f.rdbuf();
    f.close();
    return ss.str();
}

bool createShader(const char * const code , unsigned int type , unsigned int & shader){

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code,NULL);
    glCompileShader(shader);
    int status;
    char info[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(shader, 512, NULL, info);
        Log::cout( __FILE__ , type == GL_VERTEX_SHADER ? "VERTEX : " : "FRAGMENT : " , info );;
        // Log::cout( __FILE__ , );
        return false;
    }

    Log::cout( __FILE__ , type == GL_VERTEX_SHADER ? "VERTEX shader" : "FRAGMENT shader " , "successfuly " ) ;
    return true;
}

bool createProgram( const char * const vCode , const char * const fCode , unsigned int & program ){
    unsigned int vertexShader, fragmentShader ;

    bool vStatus = createShader( vCode , GL_VERTEX_SHADER , vertexShader );
    bool fStatus = createShader( fCode , GL_FRAGMENT_SHADER , fragmentShader );
    
    program = glCreateProgram();

    if (!vStatus || !fStatus) {
        Log::cout( __FILE__ , "Program : create shader failed " );;
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

bool compile( unsigned int & program ){
    
    std::string definedVertexShaderCode = readFile("/home/coder/project/c++/opengl/shader/vertex.vert");
    std::string definedFragmentShaderCode = readFile("/home/coder/project/c++/opengl/shader/fragment.frag");


    program = glCreateProgram();

    unsigned int vertexShader , fragmentShader;
    
    bool vStatus = createShader( definedVertexShaderCode.c_str()   , GL_VERTEX_SHADER   , vertexShader);
    bool fStatus = createShader( definedFragmentShaderCode.c_str() , GL_FRAGMENT_SHADER , fragmentShader);
    
    if (!vStatus || !fStatus) {
        std::cout << "Program : create shader failed " << std::endl;
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
 * @brief 
 * 
 * @param str 
 * @param mode
 * mode = 0 => delete spaces at the beginning
 * mode = 1 => delete spaces at the end
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
 * @brief 
 * 
 * @param line
 *  
 * @return std::vector< std::string > 
 */
std::vector< std::string > parseCommand( std::string line ){
    std::vector< std::string > command;

    if( line.size() <= 0 ) {
        return command;
    }else if( line.size() >= 2 && line.at(0) == '/' && line.at(1) == '/' ) {  // comment
        command.push_back( line );
    }else if( line.size() > 0  && line.at( 0 ) != '#'){                 // ordinary content
        command.push_back( line );
    }else{                                                              // command

        line = line.substr( 1 , -1 );
    
        int start = 0;
        for( int i = 0 ; i < line.size() ; ++ i ){
            if( line.at( i ) == ' ' ){
                std::string arg = line.substr( start , i - start );
                arg = trim( arg , 1 );
                if( arg.size() > 0)
                    command.push_back( arg );
                start = i + 1;
            } 
        }
        std::string arg = trim( line.substr( start , -1 ) , 1 );
        if( arg.size() > 0 ) command.push_back( arg );
    }

    

    return command;
}

/**
 * @brief execute the macro command , it's just 'include' at present
 * 
 * @param commands
 * commonds could be 'include' and 'version' currently
 * @return std::string 
 */
std::string execCommand( std::vector< std::string > commands ){

    std::string commandResult = "";

    if( commands.size() <= 0 ) return commandResult ;

    if( commands.size() == 1 ) return commands.at( 0 );
    
    if( commands.at( 0 ) == "include" && commands.size() == 2 ){

        std::string includeFile = commands.at( 1 );
        includeFile = includeFile.substr( 1 , includeFile.size() - 2 ) + ".glsl";
        commandResult = readFile( INCLUDE_LIB_FOLDER + includeFile );

    }else if( commands.at(0) == "define" ){

    }else{

        commandResult += '#';
        for( int i = 0 ; i < commands.size() ; ++ i ){
            commandResult += commands.at( i ) + ' ';
        }

    }

    return commandResult;

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
    this->isReady = false;
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
    this->version = version;
}

/**
 * @brief set the precision used in the shader
 * 
 * @param precision 
 */
void Shader::setPrecision( std::string precision ){
    this->precision = precision;
}

/**
 * @brief get the pre-processed shader coder
 * 
 * @return std::string 
 */
std::string Shader::getPreProcessedShadercode(){

    // #version 330 core
    // precision lowp float;
    // #define 

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


    std::stringstream sStream( this->shaderCode );
    while( !sStream.eof() ){
        std::string line;
        std::getline( sStream , line );
        std::vector< std::string > command = parseCommand( line );
        std::string content = execCommand( command );
        shaderCode += content + '\n';
    }
    
    return shaderCode;
    
}

/**
 * @brief compile the shader
 * 
 * @return true 
 * @return false 
 */
bool Shader::compile(){

    std::string code = this->getPreProcessedShadercode();

    this->isReady = createShader( code.c_str() , this->shaderType , this->shaderID );
    
    return this->isReady;

}

/**
 * @brief delete the buffer of the object 
 * 
 * @return true 
 * @return false 
 */
bool Shader::dispose(){

    if( !isReady ) return true;

    if( glIsShader( this->shaderID ) == GL_TRUE ) glDeleteShader( this->shaderID );

    this->isReady = false;

    return true;

}

/**
 * @brief set the macro command , such as #define 
 * 
 * @param command 
 * @param arg 
 */
void Shader::setCommand( std::string command , std::string arg ){
    
    if( this->defines.find( command ) == this->defines.end() ) this->defines.emplace( command , arg );
    else this->defines.at( command ) = arg;

}


/**
 * @brief Create Shader Object from a file directly
 * 
 * @param path 
 * @param shaderType 
 * @return Shader* 
 */
Shader * Shader::FromFile( std::string path , GLenum shaderType ){

    std::string shaderCode = readFile( path );

    Shader * shader = new Shader( shaderCode , shaderType );
    
    return shader;

}


// Program
/**
 * @brief Construct a new Program:: Program object
 * 
 * @param vertexCode 
 * @param fragmentCode 
 */
Program::Program( std::string vertexCode , std::string fragmentCode )
{

    this->vertexShader = new Shader( vertexCode , GL_VERTEX_SHADER );
    this->fragmentShader = new Shader( fragmentCode , GL_FRAGMENT_SHADER );

    this->isReady = false;

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

    this->isReady = this->vertexShader->compile() && this->fragmentShader->compile();
    
    if( !this->isReady ) return false;

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
        this->isReady = false;
        return false; 
    }

    this->isReady = true;

    this->regist();

    return this->isReady;

}

/**
 * @brief delete the buffer created in program
 * 
 * @return true 
 * @return false 
 */
bool Program::dispose(){
    if( !this->isReady ) return true;

    if( this->vertexShader != nullptr ) delete this->vertexShader;
    if( this->fragmentShader != nullptr ) delete this->fragmentShader;

    if( glIsProgram( this->UIProgramID ) == GL_TRUE ) glDeleteProgram( this->UIProgramID );

    this->vertexShader = nullptr , this->fragmentShader = nullptr ; 
    this->isReady = false;

    return true;
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
        Log::cout( __FILE__ , "regist : " , name );
    }

    // active attribute
    int attribCount = 0;
    glGetProgramiv( this->UIProgramID , GL_ACTIVE_ATTRIBUTES , &attribCount );

    for( int i = 0 ; i < attribCount ; ++ i ){
        glGetActiveAttrib( this->UIProgramID , i , maxLength , &length , &size , &type , name );
        this->attributes.emplace( name , i );
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

/**
 * @brief Create Program Object from the two given file pathes
 * TODO : This object should be destroied automaticly
 * @param vertexPath 
 * @param fragmentPath 
 * @return Program* 
 */
Program * Program::FromFile( std::string vertexPath , std::string fragmentPath ){

    std::string vertexCode = readFile( vertexPath );
    std::string fragmentCode = readFile( fragmentPath );

    return new Program( vertexCode , fragmentCode );

}
