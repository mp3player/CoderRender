
#include <iostream>
#include <opengl/shader/Program.hpp>
#include <scene/Material.hpp>
#include <render/Renderer.hpp>
#include <component/Light.hpp>



typedef MemoryManager< Program > ShaderManager;
typedef MemoryManager< Texture > TextureManager;
typedef MemoryManager< TextureBuffer > TextureBufferManager;
typedef MemoryManager< VertexArrayBuffer > VAOManager;

static ShaderManager _shaders;
static TextureManager _textures;
static TextureBufferManager _textureBuffers;
static VAOManager _vaoManager;

static int RenderReferenceCount = 0;


static std::unordered_map< Mesh * , VertexArrayBuffer * > shapeCaches;
static std::unordered_map< Material * , Program * > _shaderCaches;
static std::unordered_map< Texture * , TextureBuffer * > _textureCaches;


static Program * program = Program::FromFile( 
    "/home/coder/project/c++/engine/shader/basic/vertex.vert",
    "/home/coder/project/c++/engine/shader/basic/fragment.frag"
);


Renderer::Renderer(){
    RenderReferenceCount += 1;
    program->compile();
}

Renderer::~Renderer(){

    RenderReferenceCount -= 1;


    std::cout << RenderReferenceCount << std::endl;

    if( RenderReferenceCount <= 0 ){

        
        _shaders.clear();
        _textures.clear();
        _textureBuffers.clear();
        _vaoManager.clear();
        delete program; 
        program = nullptr ;
        Log::cout( __FILE__ , "release buffer " );

    }

}

VertexArrayBuffer * getVAO( Node * node ){
    
    assert( node != nullptr );

    MeshComponent * meshComponent = node->getComponent<MeshComponent>();

    assert( meshComponent != nullptr );
    assert( meshComponent->mesh != nullptr );

    Mesh * mesh = meshComponent->mesh;
    
    if( shapeCaches.find( mesh ) != shapeCaches.end() )
        return shapeCaches.find( mesh )->second;

    VertexArrayBuffer * vao = new VertexArrayBuffer();

    vao->init();
    vao->bind();

    AttributeFloat * position = mesh->getAttribute("position");
    AttributeFloat * texCoordinate = mesh->getAttribute("uv");
    AttributeFloat * normal = mesh->getAttribute("normal");
    // AttributeFloat * tangent = mesh->getAttribute("tangent");
    // AttributeFloat * biTangent = mesh->getAttribute("biTangent");

    vao->addAttribute( position->data , position->itemSize  );
    vao->addAttribute( texCoordinate->data , texCoordinate->itemSize );
    vao->addAttribute( normal->data , normal->itemSize );


    std::vector< unsigned int > index = mesh->getIndex();

    if( index.size() > 0 )
        vao->setIndex( index );

    _vaoManager.add( vao );
    shapeCaches.emplace( mesh , vao );
    return vao;

}

Program * getProgram( Node * node ){


    return program;
    if( node == nullptr ) return program;

    RenderComponent * renderComponent = node->getComponent< RenderComponent >();
    Material * material = renderComponent->material ;

    if( material == nullptr ){
        return program;
    }

    if( _shaderCaches.find( material ) != _shaderCaches.end() )
        return _shaderCaches.find( material )->second;

    // TODO : create shader according the material


}

void Renderer::clear(){

    glClearColor( this->clearColor.r , this->clearColor.g , this->clearColor.b , clearAlpha );
    GLenum bufferMask = GL_COLOR_BUFFER_BIT ;
    if( this->depthTest ){
        glEnable( GL_DEPTH_TEST );
        bufferMask |= GL_DEPTH_BUFFER_BIT ;
    }
       

    glClear( bufferMask );

}

void Renderer::render( Scene * nodes  ){
    
    assert( nodes != nullptr );

    Node * camera = nodes->findChildWithComponent< Camera > ();
    assert( camera != nullptr );

    Camera * eye = camera->getComponent<Camera>();
    Transform * view = camera->getComponent<Transform>();

    glm::mat4 projectionMatrix = eye->getProjectionMatrix();
    glm::mat4 viewMatrix = view->m4InverseModelTransform;
    glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;

    std::vector< Node * > alights = nodes->findChildrenWithComponent<AmbientLight>();
    std::vector< Node * > scene = nodes->findChildrenWithComponent<RenderComponent>();


    this->clear();

    for( Node * node : scene ){

        MeshComponent * meshComponent = node->getComponent<MeshComponent>();
        Transform * transform = node->getComponent<Transform>();
        RenderComponent * renderComponent = node->getComponent<RenderComponent>();
        Material * mat = renderComponent->material;

        Uniform<glm::vec3> * color = mat->getUniform<glm::vec3>( "color" );

        VertexArrayBuffer * vao = getVAO( node );
        Program * program = getProgram( node );

        program->bind();

        vao->bind();

        if( vao->hasIndex() ){

            vao->bindIndex();

            program->setUniformValue( "viewProjectionMatrix" , viewProjectionMatrix );
            program->setUniformValue( "projectionMatrix" , projectionMatrix );
            program->setUniformValue( "viewMatrix" , viewMatrix );
            program->setUniformValue( "modelMatrix" , transform->m4ModelWorldTransform );
            program->setUniformValue( "normalMatrix" , transform->m3NormalWorldMatrix );


            program->setUniformValue( "color" , color->value );

            glDrawElements( GL_TRIANGLES , meshComponent->mesh->vertexCount() , GL_UNSIGNED_INT , nullptr );

        }else{

            Log::cout( __FILE__ , meshComponent->mesh->vertexCount() );

            glDrawArrays( GL_TRIANGLES , 0 , meshComponent->mesh->vertexCount() );

        }

        vao->unBind();

    }


}



