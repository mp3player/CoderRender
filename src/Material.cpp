#include <scene/Material.hpp>
#include <iostream>



std::string UniformBuffer::getName() const {
    return this->name ;
}




Material::Material(){ 
    this->addUniformValue( "color" , glm::vec3( 1.0f) );
}

Material::~Material(){
    
    std::unordered_map< std::string , UniformBuffer * >::iterator begin = this->uniforms.begin() , end = this->uniforms.end();

    while( begin != end ){

        delete begin->second;

        begin ++;

    }

    this->uniforms.clear();

}



UniformBuffer * Material::getUniformValue( std::string name ){

    if( this->uniforms.find( name ) == this->uniforms.end() ) return nullptr ;

    return this->uniforms.at( name );

}