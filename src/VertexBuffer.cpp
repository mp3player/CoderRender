#include<core/VertexBuffer.hpp>



void VertexBuffer::init(){

    glCreateBuffers( 1 , &( this->id ) );

}

void VertexBuffer::bind(){

    glBindBuffer( this->target , this->id );

}

void VertexBuffer::unBind(){

    glBindBuffer( this->target , 0 );

}

bool VertexBuffer::allocate( int size ){

    this->bufferSize = size;
    glBufferData( this->target , size , nullptr , GL_READ_WRITE );

    return true;

}

void VertexBuffer::clearBufferData( GLenum internalFormat , GLenum format , GLenum type , void * data ){

    glClearBufferData( this->target , internalFormat , format , type , data );

}

void VertexBuffer::dispose(){

    if( glIsBuffer( this->id ) == GL_TRUE ){
        glDeleteBuffers( 1 , &(this->id) );
    }

}







// AttributeBuffer
AttributeBuffer::AttributeBuffer( int index , int itemSize , int offset )
    : index( index ) , itemSize( itemSize ) , offset( offset ) , stride( offset + itemSize )
{}

bool AttributeBuffer::bufferData( const std::vector< float > data , GLenum usage ){
    return VertexBuffer::bufferData<float>( data , usage );
}



void AttributeBuffer::enable(){

    glEnableVertexAttribArray( this->index );
    glVertexAttribPointer( this->index , this->itemSize , GL_FLOAT , GL_FALSE , this->stride * sizeof( float ) , (void *)( this->offset * sizeof( float ) ) );

}

void AttributeBuffer::disable(){

    glDisableVertexAttribArray( this->index );

}




// IndexBuffer
bool IndexBuffer::bufferData( const std::vector< unsigned int > data , GLenum usage ){
    this->pointSize = data.size();
    return VertexBuffer::bufferData< unsigned int >( data , usage );
}

int IndexBuffer::size() const {
    return this->pointSize;
}


// VertexArrayBuffer 

// If array is a name returned by glCreateVertexArrays, 
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

bool VertexArrayBuffer::hasIndex() const {
    
    return ( this->index != nullptr ) ;

}

void VertexArrayBuffer::init(){

    glCreateVertexArrays( 1 , &( this->id ) );

}

void VertexArrayBuffer::bind(){
    
    glBindVertexArray( this->id );

}

void VertexArrayBuffer::unBind(){
    
        glBindVertexArray( 0 );

}

bool VertexArrayBuffer::setIndex( std::vector< unsigned int > index ){

    if( this->index != nullptr ) {
        delete this->index;
    }

    this->index = new IndexBuffer();
    this->index->init();
    this->index->setTarget( GL_ELEMENT_ARRAY_BUFFER );
    this->index->bind();
    this->index->bufferData( index , GL_STATIC_DRAW );
    this->index->unBind();
    return true;

}

void VertexArrayBuffer::bindIndex(){

    if( this->index != nullptr )
    this->index->bind();

}

// this method can be decomposed to two section : 1. create buffer + 2. buffer
// split the two section can make the attribute global 

//  ==> glSubBufferData();
bool VertexArrayBuffer::addAttribute( std::vector< float > data , int itemSize ){

    this->pointSize = data.size() / itemSize;

    this->bind();

    AttributeBuffer * buffer = new AttributeBuffer( this->buffer.size() , itemSize , 0 );

    buffer->init();
    buffer->setTarget( GL_ARRAY_BUFFER );
    buffer->bind(  );
    buffer->bufferData( data , GL_STATIC_DRAW );
    buffer->enable();
    buffer->unBind();

    this->unBind();

    this->buffer.push_back( buffer );

    return true;

}

int VertexArrayBuffer::size() const {
    
    if( this->hasIndex() ){
        return this->index->size();
    }
    return this->pointSize;

}


