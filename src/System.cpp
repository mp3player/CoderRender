#include <system/System.hpp>
#include <functional>
#include <iostream>


System::System( Scene * scene , std::string name )
    : scene( scene ) , name( name ) , buffer( std::vector< Node * >() )
{

}

void System::createBuffer(){

    this->buffer.clear();
    std::function< void( Node *) > recursor;
    recursor = [&]( Node * node ){
        this->buffer.push_back( node );
        for( int i = 0 ; i < node->children.size() ; ++ i ){
            Node * child = node->children.at( i );
            this->buffer.push_back( child );
            recursor( child );
        }
    };

    for( Node * node : scene->children ){
        recursor( node );
    }
    
}