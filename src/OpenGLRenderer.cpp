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

std::unordered_map< Node * , Node * > shadowCamera;

Program * shadowProgram = Program::FromFile(
    "/home/coder/project/c++/engine/shader/depth/vertex.vert",
    "/home/coder/project/c++/engine/shader/depth/fragment.frag"
);


OpenGLRenderer::OpenGLRenderer(){

    RenderReferenceCount += 1;

    glEnable(GL_MULTISAMPLE);
    glClearColor( color.r , .2f , color.b , alpha );
    shadowProgram->compile();

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

        delete shadowProgram;

        auto begin = shadowCamera.begin() , end = shadowCamera.end();

        while( begin != end ){
            delete begin->second;
            begin++;
        }


    }

}

/**
 * @brief set the buffer of COLOR_BUFFER_BIT
 * 
 * @param r 
 * @param g 
 * @param b 
 */
void OpenGLRenderer::setColor( float r , float g , float b ){
    Renderer::setColor( r , g , b );
    glClearColor( r , g , b , this->alpha );
}

void OpenGLRenderer::setColor( glm::vec3 color ){
    this->setColor( color.r , color.g , color.b );
}

void OpenGLRenderer::setAlpha( float alpha ){
    Renderer::setAlpha( alpha );
    glClearColor( this->color.r , this->color.g , this->color.b , this->alpha );
}

/**
 * @brief clear COLOR_BUFFER_BIT
 * 
 */
void OpenGLRenderer::clearColorBuffer(){
    this->clear( GL_COLOR_BUFFER_BIT );
}

/**
 * @brief clear DEPTH_BUFFER_BIT
 * 
 */
void OpenGLRenderer::clearDepthBuffer(){
    this->clear( GL_DEPTH_BUFFER_BIT );
}

/**
 * @brief clear STENCIL_BUFFER_BIT
 * 
 */
void OpenGLRenderer::clearStencilBuffer(){
    this->clear( GL_STENCIL_BUFFER_BIT );
}


void OpenGLRenderer::clear( unsigned int mask ){

    glClear( mask );

}

void OpenGLRenderer::render( Scene * scene  ){


    Node * camera = scene->findChildWithComponent< Camera >();

    std::vector< Node * > ambientLights = scene->findChildrenWithComponent< AmbientLight >();
    std::vector< Node * > directionalLights = scene->findChildrenWithComponent< DirectionalLight > ();
    std::vector< Node * > spotLights = scene->findChildrenWithComponent< SpotLight >();
    std::vector< Node * > pointLights = scene->findChildrenWithComponent< PointLight >();

    std::vector< Node * > entities = scene->findChildrenWithComponent< RenderComponent >();

    for( Node * entity : entities ){

        Program * program = getProgram( entity );

        program->bind();

        this->setCamera( program , camera );

        Transform * transform = entity->getComponent< Transform >();
        program->setUniformValue( "modelMatrix" , transform->m4ModelWorldMatrix );
        program->setUniformValue( "normalMatrix" , transform->m3NormalWorldMatrix );

        this->setRenderParameter( program , entity->getComponent< RenderComponent >() );
        this->setAmbientLight( program , ambientLights );
        this->setDirectionalLight( program , directionalLights );
        this->setSpotLight( program , spotLights );
        this->setPointLight( program , pointLights );

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


void OpenGLRenderer::renderShadow( Scene * scene ){

    glEnable( GL_DEPTH_TEST );
    // generate directional light shadow
    std::vector< Node * > directionalLights = scene->findChildrenWithComponent< DirectionalLight > ();
    std::vector< Node * > objs = scene->findChildrenWithComponent< RenderComponent >();
    
    for( int i =  0 ; i < directionalLights.size() ; ++ i ){

        Node * dLight = directionalLights.at( i );

        Node * cameraNode ;
        
        // use shadowCamera 
        if( shadowCamera.find( dLight ) == shadowCamera.end() ){
        
            // create a new ShadowCamera 
            cameraNode = new Node();
            Camera * camera = new OrthogonalCamera( -8 , 8 , 8 , -8 , .1 , 100 );
            camera->update(0.0f);
            cameraNode->addComponent( camera );
            cameraNode->getComponent< Transform >()->setTranslation( dLight->getComponent< Transform >()->v3Translation );
            cameraNode->getComponent< Transform >()->setRotation( dLight->getComponent< Transform >()->v3Rotation );
            cameraNode->getComponent< Transform >()->setScale( dLight->getComponent< Transform >()->v3Scale );
        
            cameraNode->update( 0.0f );

        }else{

            // using the existing camera
            cameraNode = shadowCamera.at( dLight );

        }

        // use program ;
        

        for( Node * obj : objs ){
            shadowProgram->bind();
            this->setCamera( shadowProgram , cameraNode );
            // modelMatrix 
            shadowProgram->setUniformValue( "modelMatrix" , obj->getComponent< Transform >()->m4ModelWorldMatrix );
            // vao 
            VertexArrayBuffer * vao = getVAO( obj );
            vao->bind();

            if( vao->hasIndex() ){
                vao->bindIndex();
                glDrawElements( GL_TRIANGLES , vao->size() , GL_UNSIGNED_INT , nullptr );
            }else{
                glDrawArrays( GL_TRIANGLES , 0 , vao->size() );
            }

            vao->unBind();

        }



        // render objects using shadowProgram 




    }



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
    glm::mat4 viewMatrix = transform->m4ViewMatrix;
    glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;

    program->setUniformValue( "mainCamera.projectionMatrix" , projectionMatrix );
    program->setUniformValue( "mainCamera.viewMatrix" , viewMatrix );
    program->setUniformValue( "mainCamera.viewProjectionMatrix" , viewProjectionMatrix );
    program->setUniformValue( "mainCamera.position" , transform->v3Translation );

    // std::cout << "camera " << std::endl << projectionMatrix << std::endl;


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
        program->setUniformValue( "directionalLight.direction" , transform->v3LookAt - transform->v3Translation );

    }

    

}

/**
 * @brief Set the spot light object of current scene
 * 
 * @param program 
 * @param spots 
 */
void OpenGLRenderer::setSpotLight( Program * program , std::vector< Node * > spots ){
    
    assert( program != nullptr );

    for( int i = 0 ; i < spots.size() ; ++ i ){

        Node * node = spots.at( i );
        SpotLight * spotLight = node->getComponent< SpotLight >();
        Transform * transform = node->getComponent< Transform >();
        
        program->setUniformValue( "spotLight.color" , spotLight->color );
        program->setUniformValue( "spotLight.position" , transform->v3Translation );
        program->setUniformValue( "spotLight.direction" , glm::normalize( transform->v3LookAt - transform->v3Translation ) );
        program->setUniformValue( "spotLight.cutOff" , spotLight->cutOff );
        program->setUniformValue( "spotLight.intensity" , spotLight->intensity );


    }

}

/**
 * @brief set the point light object of current scene
 * 
 * @param program 
 * @param points 
 */
void OpenGLRenderer::setPointLight( Program * program , std::vector< Node * > points ){

    assert( program != nullptr );

    for( int i = 0 ; i < points.size() ; ++ i ){

        Node * node = points.at( i );
        PointLight * pointLight = node->getComponent< PointLight >();
        Transform * transform = node->getComponent< Transform >();
        
        program->setUniformValue( "pointLight.color" , pointLight->color );
        program->setUniformValue( "pointLight.position" , transform->v3Translation );
        program->setUniformValue( "pointLight.intensity" , pointLight->intensity );

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




/**
 * @brief this function are created to manage the buffer 
 *  
 */
// buffer ------------------------------------------------------------------------
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
        tbo->setTarget( GL_TEXTURE_2D );
        tbo->bind();
        tbo->bufferData( texture );
        tbo->unBind();

        TextureBuffers.add( tbo );
        TextureCaches.emplace( texture , tbo );

    }
    
    return TextureCaches.at( texture );

}
