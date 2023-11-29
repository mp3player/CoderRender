#include <core/Buffer.hpp>
#include <glad/glad.h>
#include <iostream>




Buffer::~Buffer(){ }

unsigned int Buffer::ID() const {
    return this->id;
}

unsigned int Buffer::getTarget() const {
    return this->target;
}

void Buffer::setTarget( unsigned int target ) {
    this->target = target;
}

