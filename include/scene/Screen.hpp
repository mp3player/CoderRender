#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <core/VertexBuffer.hpp>

struct Screen {



    public:

        VertexArrayBuffer * vao = nullptr ;

    public:

        Screen(); 
        ~Screen();

    public:

        void render();

};



#endif