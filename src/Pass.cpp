#include <render/Pass.hpp>


Pass::Pass( int width , int height )
    :width( width ) , height( height )
{}




std::vector< float > rectangle = { 1.0f , 1.0f , -1.0f , 1.0f , -1.0f , -1.0f , 1.0f , -1.0f };

std::vector< float > uv = { 1.0f , 1.0f , 0.0f , 1.0f , 0.0f , 0.0f , 1.0f , 0.0f };

std::vector< unsigned int > _index = { 0 , 1 , 2 , 0 , 2 , 3 };

FullScreenQuad::FullScreenQuad(){

    this->vao = new VertexArrayBuffer();
    this->vao->addAttribute( rectangle , 2 );
    this->vao->setIndex( _index );

    this->program = Program::FromFile( 
        "/home/coder/project/c++/engine/shader/screen/vertex.vert" ,
        "/home/coder/project/c++/engine/shader/screen/fragment.frag"
    );

    this->program->compile();

}

FullScreenQuad::~FullScreenQuad(){
    delete this->vao ;
    delete this->program;
}

void FullScreenQuad::render( RenderTexture * texture ){

    glClearColor( 1.0f , 0.0f,  0.0f ,1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    this->program->bind();

    if( texture != nullptr ){

        glBindTextureUnit( 0 , texture->ID() );
        this->program->setUniformValue( "map" , 0 );
    }

    this->vao->bind();

    glDrawElements( GL_TRIANGLES , this->vao->size() , GL_UNSIGNED_INT , 0 );

    this->vao->unBind();

}


