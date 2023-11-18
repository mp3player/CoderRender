#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include <string>
#include <scene/Texture.hpp>
#include <unordered_map>


struct UniformBuffer {

    std::string name ;

    virtual std::string getName() const ;

};

template< typename T >
struct Uniform : UniformBuffer {
    
    public:
        T value;
    public:
        Uniform( T value );
        Uniform( std::string name , T value );

};

template< typename T>
Uniform<T>::Uniform( T value )
    : value( value )
{}

template< typename T>
Uniform<T>::Uniform( std::string name , T value )
    :value( value )
{
    this->name = name;
}


typedef Uniform<float> UniformFloat ;
typedef Uniform<int> UniformInteger;

typedef Uniform<glm::vec2> UniformVec2;
typedef Uniform<glm::vec3> UniformVec3;
typedef Uniform<glm::vec4> UniformVec4;

typedef Uniform<glm::mat2> UniformMat2;
typedef Uniform<glm::mat3> UniformMat3;
typedef Uniform<glm::mat4> UniformMat4;

struct Material {

    public:
        bool castShadow = false;
        bool receiveShadow = false;

        std::unordered_map< std::string , UniformBuffer * > uniforms;

    public:

        Material();
        ~Material();

    public:

        template< typename T >
        void addUniformValue( std::string , T value );

        template< typename T >
        std::vector< T * > getUniformValues( );

        template< typename T >
        Uniform<T> * getUniform( std::string name );

        template< typename T >
        bool hasUniform( std::string name );

        template< typename T>
        bool setUniform( std::string name , T value );

    public: 

        UniformBuffer * getUniformValue( std::string name );

};



// add property to the material
template< typename T >
void Material::addUniformValue( std::string name , T value ){

    Uniform<T> * uniform = new Uniform<T>( name , value );
    this->uniforms.emplace( name , uniform );

}



// get property according the template parameter
template< typename T >
std::vector< T * > Material::getUniformValues( ){
    
    std::vector< UniformBuffer * > buffers;

    std::unordered_map< std::string , UniformBuffer * >::iterator begin = uniforms.begin() , end = uniforms.end();

    while( begin != end ){

        T * result = dynamic_cast< T * >( begin->second );
        
        if( result ){

            buffers.push_back( result  );
        
        }
        
        begin ++;

    }

    return buffers;

}



// get the uniform with a given name and template parameter
template< typename T >
Uniform<T> * Material::getUniform( std::string name ){
    
    if( this->uniforms.find( name ) == this->uniforms.end() ) return nullptr ;

    UniformBuffer * buffer = this->uniforms.at( name );

    Uniform<T> * result = dynamic_cast< Uniform<T> * >( buffer );

    if( result ){
        return result;
    }
    
    return nullptr ;


}



// check whether the material contain the property with given name and template parameter
template< typename T >
bool Material::hasUniform( std::string name ){
    
    Uniform<T> * result = this->getUniform<T>( name );

    if( result == nullptr ) return false;

    return true;

}



// set the uniform and value
template< typename T>
bool Material::setUniform( std::string name , T value ){

    Uniform<T> * result = this->getUniform<T>( name );

    if( result == nullptr ) return false;

    result->value = value;

    return true;

}





#endif