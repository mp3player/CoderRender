#include <render/ShadowPass.hpp>
#include <vector>
#include <component/Light.hpp>



ShadowPass::ShadowPass( int width , int height )
    : Pass( width , height )
{
    
    this->frameBuffer = new FrameBuffer( width , height );
    this->depthBuffer = new RenderBuffer( width , height );

    this->frameBuffer->bind();
    this->depthBuffer->bind();


    

}

ShadowPass::~ShadowPass(){
    this->dispose();
}

void ShadowPass::dispose(){

    delete this->shadowProgram;
    delete this->frameBuffer;
    delete this->depthBuffer;
    
    auto begin = this->shadowMaps.begin() , end = this->shadowMaps.end();
    while( begin != end ){
        delete begin->second;
    }

    this->shadowMaps.clear();

}


void ShadowPass::render( Scene * scene ){

    std::vector< Node * > renderable = scene->findChildrenWithComponent< RenderComponent >();
    std::vector< Node * > directionals = scene->findChildrenWithComponent< DirectionalLight >();

    for( Node * light : directionals ){

        if( this->shadowMaps.find( light ) == this->shadowMaps.end() ){

            // create a shadowmap 
            RenderTexture * shadowMap = new RenderTexture( this->width , this->height );
            shadowMap->init();


        }

    }

}




