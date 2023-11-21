#include <core/Buffer.hpp>
#include <glad/glad.h>
#include <iostream>




Buffer::~Buffer(){
    
}

unsigned int Buffer::ID() const {
    return this->id;
}
