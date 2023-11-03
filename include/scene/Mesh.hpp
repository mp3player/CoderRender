#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <core/Ref.hpp>
#include <core/MemoryManager.hpp>

// TODO : create a static source manager 

template< typename T >
struct Attribute {
    unsigned int itemSize;
    std::vector< T > data;
    explicit Attribute( unsigned int itemSize )
        : itemSize( itemSize )
    {}

    explicit Attribute( std::vector< T > data , unsigned int itemSize )
        :itemSize( itemSize ) , data( data )
    {}
};

typedef Attribute< float > AttributeFloat;
typedef Attribute< int > AttributeInteger;

struct Mesh {
    
    private:
        std::unordered_map< std::string , AttributeFloat * > attributes;
        std::vector< unsigned int > index;
        int iVertexCount = -1;
        int iTriangleCount = -1;

    public:
        Mesh();
        ~Mesh();

    public:
        void addAttribute( std::string name , AttributeFloat * attribute );
        void setIndex( std::vector< unsigned int > index );

        AttributeFloat * getAttribute( std::string name ) ;
        std::vector< unsigned int > getIndex();

    public:
        int vertexCount() const;
        int triangleCount() const ;

    public:
        static Mesh * ReadAttributeFromFile( std::string path );

};


#endif