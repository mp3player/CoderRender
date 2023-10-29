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
    this->dispose();
}

unsigned int Buffer::ID() const {
    return this->id;
}

void Buffer::init(){

    glGenBuffers( 1 , &(this->id) );

}

void Buffer::bind( GLenum target ){

    glBindBuffer( target , this->id );
    this->target = target;
    this->binded = true;

}

void Buffer::unBind(){

    if( this->binded ){
        this->binded = false;
        glBindBuffer( this->target , this->id );
    }
    
}

bool Buffer::allocate( int size ){

    if( !this->binded ) return false;

    this->bufferSize = size;
    glBufferData( this->target , size , nullptr , GL_READ_WRITE );

    return true;

}

void Buffer::clearBufferData( GLenum internalFormat , GLenum format , GLenum type , void * data ){
    
    if( !this->binded ){
        return ;
    }

    glClearBufferData( this->target , internalFormat , format , type , data );

}

void Buffer::dispose(){

    if( glIsBuffer( this->id ) == GL_TRUE ){
        glDeleteBuffers( 1 , &(this->id) );
    }

}







// AttributeBuffer
AttributeBuffer::AttributeBuffer( int index , int itemSize , int offset )
    : index( index ) , itemSize( itemSize ) , offset( offset ) , stride( offset + itemSize )
{}

bool AttributeBuffer::bufferData( const std::vector< float > data , GLenum usage ){
    return Buffer::bufferData<float>( data , usage );
}

void AttributeBuffer::enable(){

    if(!this->binded ) return ;
    glEnableVertexAttribArray( this->index );
    glVertexAttribPointer( this->index , this->itemSize , GL_FLOAT , GL_FALSE , this->stride * sizeof( float ) , (void *)( this->offset * sizeof( float ) ) );
    

}

void AttributeBuffer::disable(){

    glDisableVertexAttribArray( this->index );

}




// IndexBuffer
bool IndexBuffer::bufferData( const std::vector< unsigned int > data , GLenum usage ){
    return Buffer::bufferData< unsigned int >( data , usage );
}



// VertexArrayBuffer 

// If array is a name returned by glGenVertexArrays, 
// by that has not yet been bound through a call to glBindVertexArray, 
// then the name is not a vertex array object and glIsVertexArray returns GL_FALSE

VertexArrayBuffer::~VertexArrayBuffer(){
    
    this->unBind();
    if( this->index != nullptr ) {
        delete this->index;
        this->index = nullptr;
    }

    for( AttributeBuffer * attr : this->buffer ){
        delete attr;
    }

    this->buffer.clear();


}

unsigned int VertexArrayBuffer::ID() const {
    return this->id;
}

void VertexArrayBuffer::init(){

    glGenVertexArrays( 1 , &this->id );

}

void VertexArrayBuffer::bind(){
    
    glBindVertexArray( this->id );
    this->binded = true;

}

void VertexArrayBuffer::unBind(){

    if( this->binded ) {
        glBindVertexArray( 0 );
    }

}

bool VertexArrayBuffer::addIndex( std::vector< unsigned int > index ){

    if( !this->binded ) return false;

    this->index = new IndexBuffer();
    this->index->bind( GL_ELEMENT_ARRAY_BUFFER );
    this->index->bufferData( index , GL_STATIC_DRAW );
    this->index->unBind();
    return true;

}

// this method can be decomposed to two section : 1. create buffer + 2. buffer
// split the two section can make the attribute global 

//  ==> glSubBufferData();
bool VertexArrayBuffer::addAttribute( const AttributeFloat * attribute ){

    if( !this->binded ) return false ;

    this->bind();

    AttributeBuffer * buffer = new AttributeBuffer( this->buffer.size() , attribute->itemSize , 0 );

    buffer->init();
    buffer->bind( GL_ARRAY_BUFFER );
    buffer->bufferData( attribute->data , GL_STATIC_DRAW );
    buffer->enable();
    buffer->unBind();

    this->unBind();

    this->buffer.push_back( buffer );

    return true;

}

void VertexArrayBuffer::setAttribute( std::vector< AttributeFloat * > attributes ) {
    
}
