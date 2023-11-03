#include <system/RenderSystem.hpp>
#include <iostream>
#include <core/MemoryManager.hpp>
#include <core/Log.hpp>
#include <component/Camera.hpp>



Program * program = Program::FromFile( 
    "/home/coder/project/c++/engine/shader/basic/vertex.vert",
    "/home/coder/project/c++/engine/shader/basic/fragment.frag"
);

unsigned int ebo;

RenderSystem::RenderSystem( Scene * scene , std::string name )
    : System( scene , name )
{
    program->compile();
}

RenderSystem::~RenderSystem(){

    this->_shaders.clear();
    this->_textures.clear();
    this->_textureBuffers.clear();
    this->_vaoManager.clear();

    delete program;

    if( glIsBuffer( ebo ) ){
        glDeleteBuffers( 1 , &ebo );
    }

}

void RenderSystem::createBuffer(){

    System::createBuffer();

    std::vector< int > invisible ;

    this->cameras.clear();
    this->ambientLights.clear();
    this->directionalLights.clear();
    this->spotLights.clear();

    for( int i = 0 ; i < this->buffer.size() ; ++ i ){
        
        Node * node = this->buffer.at( i );
        
        if( node->hasComponent( "camera" ) ){

            invisible.push_back( i );
            this->cameras.push_back( node );
            mainCamera = node;

        }else if( node->hasComponent( "light" ) ){
            
            invisible.push_back( i );
            Light * light = (Light *)( node->findComponent( "light" ) );
            
            switch( light->lightType() ){

                case AMBIENT : {
                    
                    AmbientLight * aLight = ( AmbientLight * )light;
                    this->ambientLights.push_back( aLight );

                }break;

                case DIRECTIONAL : {

                    DirectionalLight * dLight = ( DirectionalLight * )light;
                    this->directionalLights.push_back( dLight );
                    
                }break;

                case SPOT : {

                    SpotLight * sLight = ( SpotLight * )light;
                    this->spotLights.push_back( sLight );

                }break;

            }


        }else{

        }

    }

    for( int i = invisible.size() - 1 ; i >=0 ; --i ){
        this->buffer.erase( this->buffer.begin() + invisible.at( i ) );
    }


}

VertexArrayBuffer * RenderSystem::getVAO( Node * node ) {

    if( node == nullptr ) return nullptr;

    MeshComponent * meshComponent = ( MeshComponent * ) node->findComponent("mesh");
    Mesh * mesh = meshComponent->mesh;

    if( meshComponent == nullptr || mesh == nullptr ) return nullptr;
    
    if( this->shapeCaches.find( mesh ) != this->shapeCaches.end() )
        return this->shapeCaches.find( mesh )->second;

    VertexArrayBuffer * vao = new VertexArrayBuffer();

    vao->init();
    vao->bind();

    AttributeFloat * position = mesh->getAttribute("position");
    AttributeFloat * texCoordinate = mesh->getAttribute("uv");
    // AttributeFloat * normal = mesh->getAttribute("normal");
    // AttributeFloat * tangent = mesh->getAttribute("tangent");
    // AttributeFloat * biTangent = mesh->getAttribute("biTangent");

    vao->addAttribute( position->data , position->itemSize  );
    vao->addAttribute( texCoordinate->data , texCoordinate->itemSize );
    // vao->addAttribute( normal->data , normal->itemSize );


    std::vector< unsigned int > index = mesh->getIndex();
    if( index.size() > 0 ){
        vao->setIndex( index );
    }

    this->_vaoManager.add( vao );
    this->shapeCaches.emplace( mesh , vao );
    return vao;

}

Program * RenderSystem::getProgram( Node * node ){
    
    if( node == nullptr ) return program;

    RenderComponent * renderComponent = ( RenderComponent * ) node->findComponent( "render" );
    Material * material = renderComponent->material ;

    if( material == nullptr ){
        return program;
    }

    if( this->_shaderCaches.find( material ) != this->_shaderCaches.end() )
        return this->_shaderCaches.find( material )->second;

    // TODO : create shader according the material
    

}

void RenderSystem::init(){
    
}

void RenderSystem::update( float deltaTime ){

    this->createBuffer();

    if( this->mainCamera == nullptr ) return ;
    this->mainCamera->update( deltaTime );
    Camera * camera = ( Camera * ) this->mainCamera->findComponent( "camera" );
    glm::mat4 projectionMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = ( (TransformComponent *) this->mainCamera->findComponent( "transform" ) )->m4InverseModelTransform;


    for( Node * node : this->buffer ){

        node->update( deltaTime );

        if( node->hasComponent( "render" ) ){

            MeshComponent * meshComponent = ( MeshComponent* ) node->findComponent( "mesh" );
            TransformComponent * transformComponent = ( TransformComponent * ) node->findComponent( "transform" );

            VertexArrayBuffer * vao = this->getVAO( node );
            Program * program = this->getProgram( node );

            program->bind();

            for( int i = 0 ; i < this->ambientLights.size() ; ++ i ){

                AmbientLight * ambientLight = this->ambientLights.at( i );
                program->setUniformValue( "ambientLight_" + std::to_string( i ) + ".color" , ambientLight->color );
                program->setUniformValue( "ambientLight_" + std::to_string( i ) + ".intensity" , ambientLight->intensity );

            }

            vao->bind();

            if( vao->hasIndex() ){

                vao->bindIndex();
                program->setUniformValue( "projectionMatrix" , projectionMatrix );
                program->setUniformValue( "viewMatrix" , viewMatrix );
                glDrawElements( GL_TRIANGLES , meshComponent->mesh->vertexCount() , GL_UNSIGNED_INT , nullptr );

            }else{

                glDrawArrays( GL_TRIANGLES , 0 , meshComponent->mesh->vertexCount() );

            }

        }
    }
}