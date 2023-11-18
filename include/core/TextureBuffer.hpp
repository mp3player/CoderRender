#ifndef _TEXTURE_BUFFER_HPP_
#define _TEXTURE_BUFFER_HPP_

#include <core/Buffer.hpp>

struct TextureBuffer : Buffer {
    

    public:
        void init() override ;
        void bind( GLenum target ) override ;
        void unBind() override ;

        void dispose() override ;

    public: 
        void bind();


};


#endif