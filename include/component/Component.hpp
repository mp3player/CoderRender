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
        virtual ~Component();

        void setNode( Node * node );

        Node * getNode( ) const ;

        std::string getName() const ;

        template< typename T > 
        T findComponent(  );

    public:
    
        virtual void init() = 0;

        virtual void update( float deltaTime ) = 0 ;

        virtual void update();

    public :
        bool isUpdated() ;

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

        Material * material = new Material() ;

    public:

        explicit RenderComponent( );
        ~RenderComponent();

    public:

        void init() override;
        void update( float deltaTime ) override ;

};



#endif