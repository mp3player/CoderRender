#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

#include <core/Ref.hpp>
#include <vector>
#include <glad/glad.h>
#include <iostream>


// 1. create buffer : glGenBuffer
// 2. bind buffer   : glBindBuffer
// 3. allocate      : glBufferData( NULL )
// 4. buffer data   : glBufferData( data )
// 5. use buffer    : glVertexAttribPointer + glEnableVertexAttribArray + glBindBuffer

struct Buffer : Ref {

    protected:

        unsigned int id = 0;
        unsigned int target = 0;
        bool binded = false;
        bool valid = false;

    protected:

        int bufferSize = 0 ;

    public:

        virtual ~Buffer();

    public:

        unsigned int ID() const ;

    public:

        virtual void init();
        virtual void bind( GLenum target );
        virtual void unBind();

    public:

        // glBufferData( target = target , size , *data = 0 , usage = read_and_write );
        bool allocate( int size );

        // glBufferData( target = target , size = size , *data , usage );
        template< typename T >
        bool bufferData( std::vector< T > data , GLenum usage );

        template< typename T >
        bool bufferSubData( std::vector< T > data , unsigned int offset );

        // glClearBufferData( target = target , internalFormat , format , type , *data)
        void clearBufferData( GLenum internalFormat , GLenum format , GLenum type , void * data );


    public:

        // glDeleteBuffers()
        virtual void dispose();

};

template< typename T >
bool Buffer::bufferSubData( std::vector< T > data , unsigned int offset ){

    if( !this->binded || this->bufferSize <= 0 ){
        return false;
    }

    glBufferSubData( this->target , offset , sizeof( T ) * data.size() , data.data() );

}

template< typename T> 
bool Buffer::bufferData( const std::vector< T > data , GLenum usage ){
    
    if( !this->binded ) return false;
    this->bufferSize = data.size() * sizeof( T );
    glBufferData( this->target , this->bufferSize , data.data() , usage );
    return true;

}







// Attribute Buffer
struct AttributeBuffer : Buffer {

    private:

        unsigned int index;
        unsigned int itemSize;
        unsigned int stride;
        unsigned int offset = 0;

    public: 

        explicit AttributeBuffer( int index , int itemSize , int offset = 0 );


    public:

        bool bufferData( const std::vector< float > data , GLenum usage );

    public:

        void enable();
        void disable();

};






// Index Buffer
struct IndexBuffer : Buffer {

    public: 

        bool bufferData( const std::vector< unsigned int > data , GLenum usage );

};






// VertexArray Buffer 
struct VertexArrayBuffer {

    private:

        unsigned int id;
        bool binded = false;
        std::vector< AttributeBuffer * > buffer;
        IndexBuffer * index = nullptr ;

    public:

        ~VertexArrayBuffer();

    public:

        unsigned int ID() const ;
        bool hasIndex() const ;

    public:

        void init();
        void bind();
        void unBind();
        void bindIndex();

    public:

        bool setIndex( std::vector< unsigned int > index );
        bool addAttribute( std::vector< float > attribute , int itemSize );


};




#endif