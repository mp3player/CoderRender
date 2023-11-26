#include <scene/Material.hpp>
#include <iostream>
#include <core/MemoryManager.hpp>
#include <core/Log.hpp>


typedef MemoryManager< Texture > TextureManager;

static TextureManager Manager;

static int MaterialReferenceCount = 0;






Material::Material(){ 
    this->addUniformValue( "color" , glm::vec3( 1.0f ) );
    MaterialReferenceCount += 1;
}

Material::~Material(){
    
    std::unordered_map< std::string , UniformBuffer * >::iterator begin = this->uniforms.begin() , end = this->uniforms.end();

    while( begin != end ){

        delete begin->second;

        begin ++;

    }

    this->uniforms.clear();

    MaterialReferenceCount -= 1;

    if( MaterialReferenceCount <= 0 ){
        Log::cout( __FILE__ , "release texture resource");
        Manager.clear();
    }

}

UniformBuffer * Material::getUniformValue( std::string name ){

    if( this->uniforms.find( name ) == this->uniforms.end() ) return nullptr ;

    return this->uniforms.at( name );

}

std::vector< std::string > Material::keys(){
    
    std::vector< std::string > results;
    std::unordered_map< std::string , UniformBuffer * >::iterator begin = this->uniforms.begin() , end = this->uniforms.end() ;

    while( begin != end ){

        results.push_back( begin->first );

        begin ++;
    }

    return results;

}

template<>
void Material::addUniformValue<Texture *>( std::string name , Texture * value ){

    Manager.add( value );
    Uniform<Texture *> * uniform = new Uniform<Texture *>( name , value );
    this->uniforms.emplace( name , uniform );

}


