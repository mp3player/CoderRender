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
        bool valid = false;

    protected:

        int bufferSize = 0 ;

    public:

        virtual ~Buffer();

    public:

        unsigned int ID() const ;
        unsigned int getTarget() const ;

    public:

        virtual void init() = 0;
        virtual void bind() = 0;
        virtual void unBind() = 0;

        // glDeleteBuffers()
        virtual void dispose() = 0;

    public:
        void setTarget( GLenum target );

};




#endif