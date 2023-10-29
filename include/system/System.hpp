#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_

#include <string>
#include <scene/Scene.hpp>

struct System {

    protected :
        std::string name;
        Scene * scene;
        std::vector< Node * > buffer ;

    public:
        explicit System( Scene * scene , std::string name = "System" );

    protected:
        void createBuffer();

    public:
        virtual void init() = 0;

        virtual void update( float deltaTime ) = 0;


};


#endif