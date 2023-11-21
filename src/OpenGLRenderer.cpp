#include <render/OpenGLRenderer.hpp>
#include <algorithm>
#include <opengl/shader/OpenGLProgram.hpp>
#include <scene/Material.hpp>
#include <component/Light.hpp>
#include <core/TextureBuffer.hpp>
#include <core/VertexBuffer.hpp>
#include <component/Transform.hpp>
#include <core/Log.hpp>

typedef MemoryManager< Program > ShaderManager;
typedef MemoryManager< TextureBuffer > TextureBufferManager;
typedef MemoryManager< VertexArrayBuffer > VAOManager;

static ShaderManager Shaders;
static TextureBufferManager TextureBuffers;
static VAOManager VaoManager;

static int RenderReferenceCount = 0;

static std::unordered_map< Mesh * , VertexArrayBuffer * > ShapeCaches;
static std::unordered_map< std::string , Program * > ProgramCaches;
static std::unordered_map< Texture * , TextureBuffer * > TextureCaches;



OpenGLRenderer::OpenGLRenderer(){

    RenderReferenceCount += 1;
    glClearColor( color.r , color.g , color.b , alpha );

}

OpenGLRenderer::~OpenGLRenderer(){

    RenderReferenceCount -= 1;

    if( RenderReferenceCount <= 0 ){

        Shaders.clear();
        TextureBuffers.clear();
        VaoManager.clear();

        Log::cout( __FILE__ , "release shader  " );
        Log::cout( __FILE__ , "release texture buffer " );
        Log::cout( __FILE__ , "release vertex buffer " );

    }

}

void OpenGLRenderer::clear(){

    glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

}


/**
 * @brief Set the Camera object of current scene
 * 
 * @param program 
 * @param camera 
 */
void OpenGLRenderer::setCamera( Program * program , Node * cameraNode ){
    
    assert( program != nullptr && cameraNode != nullptr );

    Camera * camera = cameraNode->getComponent<Camera>();
    Transform * transform = cameraNode->getComponent<Transform>();

    glm::mat4 projectionMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = transform->m4InverseModelTransform;
    glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;

    program->setUniformValue( "mainCamera.projectionMatrix" , projectionMatrix );
    program->setUniformValue( "mainCamera.viewMatrix" , viewMatrix );
    program->setUniformValue( "mainCamera.viewProjectionMatrix" , viewProjectionMatrix );
    program->setUniformValue( "mainCamera.position" , transform->v3Translation );

}

/**
 * @brief Set the Ambient Light object of current scene
 * 
 * @param program 
 * @param ambients 
 */
void OpenGLRenderer::setAmbientLight( Program * program , std::vector< Node * > ambients ){

    assert( program != nullptr );

    for( int i = 0 ; i < ambients.size() ; ++ i ){
        Node * node = ambients.at( i );
        AmbientLight * ambient = node->getComponent< AmbientLight >();

        program->setUniformValue( "ambientLight.color" , ambient->color * ambient->intensity );

    }

}

/**
 * @brief Set the Directional Light object of current scene
 * 
 * @param program 
 * @param directionals 
 */
void OpenGLRenderer::setDirectionalLight( Program * program , std::vector< Node * > directionals ){

    assert( program != nullptr );

    for( int i = 0 ; i < directionals.size() ; ++ i ){
        
        Node * node = directionals.at( i );
        DirectionalLight * directionalLight = node->getComponent< DirectionalLight >();
        Transform * transform = node->getComponent< Transform >();
        
        program->setUniformValue( "directionalLight.color" , directionalLight->color * directionalLight->intensity );
        program->setUniformValue( "directionalLight.direction" , transform->v3LookAt );
        std::cout << transform->v3LookAt << std::endl;

    }

}

/**
 * @brief Set the Render Parameter of object 
 * 
 * @param program 
 * @param parameters 
 */
void OpenGLRenderer::setRenderParameter( Program * program , RenderComponent * parameters ){

    assert( program != nullptr && parameters != nullptr && parameters->material != nullptr );
    Material * material = parameters->material;

    program->setUniformValue( "color" , material->color );

    if( material->hasUniform< Texture *>( "map" ) ){

        Uniform< Texture * > * texture = material->getUniform< Texture * >( "map" );

        TextureBuffer * tbo = getTexture( texture->value );
        glBindTextureUnit( 0 , tbo->ID() );
        program->setUniformValue( "map" , 0 );

    }

    if( material->hasUniform< Texture *>( "normalMap" ) ){

        Uniform< Texture * > * texture = material->getUniform< Texture * >( "normalMap" );
        TextureBuffer * tbo = getTexture( texture->value );
        glBindTextureUnit( 1 , tbo->ID() );
        program->setUniformValue( "normalMap" , 1 );

    }

    if( material->depthTest ){
        glEnable( GL_DEPTH_TEST );
    }else{
        glDisable( GL_DEPTH_TEST );
    }

}




void OpenGLRenderer::render( Scene * scene  ){


    Node * camera = scene->findChildWithComponent< Camera >();
    std::vector< Node * > ambientLights = scene->findChildrenWithComponent< AmbientLight >();
    std::vector< Node * > directionalLights = scene->findChildrenWithComponent< DirectionalLight > ();
    std::vector< Node * >entities = scene->findChildrenWithComponent< RenderComponent >();

    for( Node * entity : entities ){

        Program * program = getProgram( entity );

        program->bind();

        this->setCamera( program , camera );

        Transform * transform = entity->getComponent< Transform >();
        program->setUniformValue( "modelMatrix" , transform->m4ModelTransform );
        program->setUniformValue( "normalMatrix" , transform->m3NormalMatrix );

        this->setRenderParameter( program , entity->getComponent< RenderComponent >() );
        this->setAmbientLight( program , ambientLights );
        this->setDirectionalLight( program , directionalLights );

        VertexArrayBuffer * vao = getVAO( entity );
        vao->bind();
        

        if( vao->hasIndex() ){

            vao->bindIndex();

            glDrawElements( GL_TRIANGLES , vao->size() , GL_UNSIGNED_INT , nullptr );

        }else{

            glDrawArrays( GL_TRIANGLES , 0 , vao->size() );

        }

        glBindTexture( GL_TEXTURE_2D , 0 );
        vao->unBind();


    }


}




// tools 
VertexArrayBuffer * getVAO( Node * node ){
    
    assert( node != nullptr );

    MeshComponent * meshComponent = node->getComponent<MeshComponent>();

    assert( meshComponent != nullptr );
    assert( meshComponent->mesh != nullptr );

    Mesh * mesh = meshComponent->mesh;
    
    if( ShapeCaches.find( mesh ) != ShapeCaches.end() )
        return ShapeCaches.find( mesh )->second;

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


    VaoManager.add( vao );
    ShapeCaches.emplace( mesh , vao );

    return vao;

}

Program * getProgram( Node * node ){

    assert( node != nullptr );

    RenderComponent * renderComponent = node->getComponent< RenderComponent >();
    Material * material = renderComponent->material ;


    std::vector< std::string > keys = material->keys();

    std::sort( keys.begin() , keys.end() , []( std::string a , std::string b ){ return a > b; } );

    std::string hash = "";
    for( std::string key : keys ) hash += key;

    if( ProgramCaches.find( hash ) == ProgramCaches.end() ){
        
        Program * program = new Program();

        // set commond of material
        if( material->hasUniform<Texture *>( "map" ) ){
            program->setDefine( "USE_MAP" );
        }

        if( material->lightEffect ){
            program->setDefine( "USE_LIGHT" );
        }

        ProgramCaches.emplace( hash , program );
        Shaders.add( program );

    }

    Program * _p = ProgramCaches.at( hash );
    if( _p->needUpdate() ){
        _p->update();
    }

    return ProgramCaches.at( hash );

}

TextureBuffer * getTexture( Texture * texture ){

    assert( texture != nullptr );

    if( TextureCaches.find( texture ) == TextureCaches.end() ){

        TextureBuffer * tbo = new TextureBuffer();

        tbo->init();
        tbo->bind();
        tbo->bufferData( texture );
        tbo->unBind();

        TextureBuffers.add( tbo );
        TextureCaches.emplace( texture , tbo );

    }
    
    return TextureCaches.at( texture );

}
