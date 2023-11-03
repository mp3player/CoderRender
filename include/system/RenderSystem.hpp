#ifndef _SYSTEM_RENDER_HPP_
#define _SYSTEM_RENDER_HPP_

#include <system/System.hpp>

#include <opengl/shader/Program.hpp>
#include <core/Buffer.hpp>
#include <core/MemoryManager.hpp>
#include <component/Camera.hpp>
#include <component/Light.hpp>



typedef MemoryManager< Program > ShaderManager;
typedef MemoryManager< Texture > TextureManager;
typedef MemoryManager< TextureBuffer > TextureBufferManager;
typedef MemoryManager< VertexArrayBuffer > VAOManager;


struct RenderSystem : System {

    private:
    
        ShaderManager _shaders;
        TextureManager _textures;
        TextureBufferManager _textureBuffers;
        VAOManager _vaoManager;
        

        std::unordered_map< Mesh * , VertexArrayBuffer * > shapeCaches;
        std::unordered_map< Material * , Program * > _shaderCaches;
        std::unordered_map< Texture * , TextureBuffer * > _textureCaches;

    public:

        Node * mainCamera = nullptr ;
        std::vector< Node * > cameras;
        std::vector< AmbientLight * > ambientLights;
        std::vector< DirectionalLight * > directionalLights;
        std::vector< SpotLight * > spotLights;

    public:

        RenderSystem( Scene * scene , std::string name = "render");
        ~RenderSystem();

    public:

        void createBuffer();

    public:

        VertexArrayBuffer * getVAO( Node * node ) ;
        Program * getProgram( Node * node );

    public:
    
        void init();

        void update( float deltaTime );

};

#endif