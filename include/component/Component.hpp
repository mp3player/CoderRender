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
        explicit Component( std::string name = "Component" );

        void setNode( Node * node );

        Node * getNode( ) const ;

        std::string getName() const ;

        virtual void init() = 0;

        virtual void update( float deltaTime ) = 0 ;

        template< typename T > 
        T findComponent(  );

    public :
        bool isUpdated() ;

};

struct TransformComponent : Component {

    public:
        glm::vec3 v3Translation;
        glm::vec3 v3Scale;
        glm::vec3 v3Rotation;
        glm::mat4 transform;

    public:
        TransformComponent( std::string name = "transform" );

    public:
        void setTranslation( glm::vec3 ) ;
        void setRotation( glm::vec3 );
        void setScale( glm::vec3 );

        void translate( float x = 0.0f , float y = 0.0f , float z = 0.0f ); 
        void scale( float x = 1.0f , float y = 1.0f , float z = 1.0f );
        void rotate( float x = 0.0f , float y = 0.0f , float z = 0.0f );

        glm::mat4 getTransformMatrix();

    public:
        void init() override;

        void update( float deltaTime ) override ;

};

struct MeshComponent : Component {

    public:
        Mesh * mesh;

    public:
        explicit MeshComponent( Mesh * mesh , std::string name = "mesh" );
        ~MeshComponent();

    public:
        void init() override;
        void update( float deltaTime ) override;

};

struct RenderComponent : Component {

    public:

        Material * material;

        void init() override;
        void update( float deltaTime ) override ;

};



#endif