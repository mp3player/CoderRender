#include <core/Buffer.hpp>
#include <glad/glad.h>
#include <iostream>



// unsigned int vao , vbo;

// glGenVertexArrays( 1 , &vao );
// glBindVertexArray( vao );

// glGenBuffers( 1 , &vbo );
// glBindBuffer( GL_ARRAY_BUFFER , vbo );
// glBufferData( GL_ARRAY_BUFFER , sizeof( float ) * position->data.size() , position->data.data() , GL_STATIC_DRAW );

// glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof( float ) , ( void * ) 0 );
// glEnableVertexAttribArray( 0 );


Buffer::~Buffer(){
    
}

unsigned int Buffer::ID() const {
    return this->id;
}
