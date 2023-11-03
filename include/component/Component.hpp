#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

#include <glm/glm.hpp>
#include <scene/Mesh.hpp>
#include <scene/Material.hpp>
#include <string>
#include <scene/Node.hpp>


struct Node;

struct Component {

    protected:
        Node * node;

        std::string name;

        bool needUpdate = true;

    public:
        Component( );

        void setNode( Node * node );

        Node * getNode( ) const ;

        std::string getName() const ;



        template< typename T > 
        T findComponent(  );

    public:
    
        virtual void init() = 0;

        virtual void update( float deltaTime ) = 0 ;

    public :
        bool isUpdated() ;

};

const glm::vec3 O = glm::vec3( 0.0f , 0.0f , 0.0f );
const glm::vec3 X = glm::vec3( 1.0f , 0.0f , 0.0f );
const glm::vec3 Y = glm::vec3( 0.0f , 1.0f , 0.0f );
const glm::vec3 Z = glm::vec3( 0.0f , 0.0f , 1.0f );

struct TransformComponent : Component {

    public:
        
        glm::vec3 v3Translation = O;
        glm::vec3 v3Scale = glm::vec3( 1.0f , 1.0f , 1.0f );
        glm::vec3 v3Rotation = O;

        glm::vec3 v3LookAt = -Z;
        glm::vec3 v3Right = X;
        glm::vec3 v3Up = Y;


    public:
        
        glm::mat4 m4ModelTransform;
        glm::mat4 m4InverseModelTransform;
        glm::mat4 m4WorldTransform;
        glm::mat4 m4InverseWorldTransform;
        glm::mat4 m4ModelWorldTransform;
        glm::mat4 m4InverseModelWorldTransform;

    public:

        TransformComponent(  );

    public:

        void setTranslation( glm::vec3 ) ;
        void setRotation( glm::vec3 );
        void setScale( glm::vec3 );

        void translate( float x = 0.0f , float y = 0.0f , float z = 0.0f ); 
        void scale( float x = 1.0f , float y = 1.0f , float z = 1.0f );
        void rotate( float x = 0.0f , float y = 0.0f , float z = 0.0f );

    public:

        void setWorldTransform( glm::mat4 worldTransform , glm::mat4 inverseWorldTransform );
        void updateTransform();
        void updateModelWorldTransform();

    public:
        void init() override;

        void update( float deltaTime ) override ;

};

struct MeshComponent : Component {

    public:
        Mesh * mesh;

    public:
        explicit MeshComponent( Mesh * mesh );
        ~MeshComponent();

    public: 
        unsigned int vertexCount() const;

    public:
        void init() override;
        void update( float deltaTime ) override;

};

struct RenderComponent : Component {

    public:

        Material * material = nullptr ;

    public:

        explicit RenderComponent( );

    public:

        void init() override;
        void update( float deltaTime ) override ;

};



#endif