#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include <string>
#include <scene/Texture.hpp>
#include <unordered_map>
#include <core/Uniform.hpp>

struct Material {

    public:
        bool castShadow = false;
        bool receiveShadow = false;
        bool vertexColor = false;
        bool lightEffect = true;

        bool depthTest = true;
        float alphaTest = 0.0f;

        GLenum side = GL_FRONT;

        float specular = 0.5f;

    public:
        
        glm::vec3 color = glm::vec3( 1.0f );
        
        Texture * map = nullptr ;
        Texture * normalMap = nullptr ;


    public:

        std::unordered_map< std::string , UniformBuffer * > uniforms;

    public:

        Material();
        ~Material();

    public: 

        /**
         * @brief Get the Uniform Value object
         * 
         * @param name 
         * @return UniformBuffer* 
         */
        UniformBuffer * getUniformValue( std::string name );

        /**
         * @brief get the keys of uniform values
         * 
         * @return std::vector< std::string > 
         */
        std::vector< std::string > keys();

    public:
        
        /**
         * @brief add a named uniform value to the material;
         * 
         * @tparam T 
         * @param value 
         */
        template< typename T >
        void addUniformValue( std::string , T value );

        /**
         * @brief Get the Uniform Values object
         * 
         * @tparam T 
         * @return std::vector< T * > 
         */
        template< typename T >
        std::vector< T * > getUniformValues( );

        /**
         * @brief Get the Uniform object with given name and type
         * 
         * @tparam T 
         * @param name 
         * @return Uniform<T>* 
         */
        template< typename T >
        Uniform<T> * getUniform( std::string name );

        /**
         * @brief check wheter there exists a uniform object in the mateiral with given name and type
         * 
         * @tparam T 
         * @param name 
         * @return true 
         * @return false 
         */
        template< typename T >
        bool hasUniform( std::string name );

        /**
         * @brief Set the Uniform object value 
         * 
         * @tparam T 
         * @param name 
         * @param value 
         * @return true 
         * @return false 
         */
        template< typename T>
        bool setUniform( std::string name , T value );


};


template< typename T >
void Material::addUniformValue( std::string name , T value ){

    Uniform<T> * uniform = new Uniform<T>( name , value );
    this->uniforms.emplace( name , uniform );

}


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


template< typename T >
bool Material::hasUniform( std::string name ){
    
    Uniform<T> * result = this->getUniform<T>( name );

    if( result == nullptr ) return false;

    return true;

}


template< typename T>
bool Material::setUniform( std::string name , T value ){

    Uniform<T> * result = this->getUniform<T>( name );

    if( result == nullptr ) return false;

    result->value = value;

    return true;

}





#endif