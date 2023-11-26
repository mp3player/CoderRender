#ifndef _UNIFORM_HPP_
#define _UNIFORM_HPP_

#include <string>
#include <glm/glm.hpp>
#include <scene/Texture.hpp>

enum UniformType {
    Float , Integer , Vec2 , Vec3 , Vec4 , Mat2 , Mat3 , Mat4 , Texture2D
};

struct UniformBuffer {

    std::string name ;
    std::string type ;

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

template< typename T >
Uniform<T>::Uniform( T value )
    : value( value )
{}

template< typename T >
Uniform<T>::Uniform( std::string name , T value )
    :value( value )
{
    this->name = name;
}


typedef Uniform<float> UniformFloat;
typedef Uniform<int> UniformInteger;

typedef Uniform<glm::vec2> UniformVec2;
typedef Uniform<glm::vec3> UniformVec3;
typedef Uniform<glm::vec4> UniformVec4;

typedef Uniform<glm::mat2> UniformMat2;
typedef Uniform<glm::mat3> UniformMat3;
typedef Uniform<glm::mat4> UniformMat4;
typedef Uniform< Texture * > UniformTexture;



#endif 