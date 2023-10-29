#include <scene/Mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <functional>
#include <iostream>




Mesh::Mesh(){
    this->attributes = std::unordered_map< std::string , AttributeFloat * >();
    this->vertexCount = 0;
    this->triangleCount = 0;
}

Mesh::~Mesh(){

    auto begin = this->attributes.begin() , end = this->attributes.end();
    while( begin != end ){
        delete begin->second;
        begin ++;
    }
    this->attributes.clear();

    std::cout << "release mesh" << std::endl;

}

void Mesh::setAttribute( std::string name , AttributeFloat * attribute ){
    if( this->attributes.find( name ) == this->attributes.end() && attribute->data.size() > 0 ){
        this->attributes.emplace( name , attribute );
        
    }
}

AttributeFloat * Mesh::getAttribute( std::string name ){
    
    if( this->attributes.find( name ) != this->attributes.end() ){
        return this->attributes.find( name )->second;
    }
    return nullptr ;

}

void Mesh::setIndex( std::vector< unsigned int > index ){
    this->index = index;
}

std::vector< unsigned int > Mesh::getIndex( ){
    return this->index;
}
// TODO : mesh data should be stored in Resource Manager


Assimp::Importer importer;

Mesh * parseNode( aiNode * node , const aiScene * scene );

Mesh * Mesh::ReadAttributeFromFile( std::string path ){

    const aiScene * scene = importer.ReadFile( path , aiProcess_GenNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace );
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        return nullptr ; 
    }

    AttributeFloat * coordinate = new AttributeFloat( 3 );
    AttributeFloat * texCoordinate = new AttributeFloat( 2 );
    AttributeFloat * normal = new AttributeFloat( 3 );
    AttributeFloat * tangent = new AttributeFloat( 3 );
    AttributeFloat * biTangent = new AttributeFloat( 3 );

    std::vector< unsigned int > index;

    std::function< void( aiMesh * , const aiScene * ) > parseMesh = [&]( aiMesh * mesh , const aiScene * scene ){
        
        for( int i = 0 ; i < mesh->mNumVertices ; ++ i ){
            // coordinate
            float x = mesh->mVertices[i].x ;
            float y = mesh->mVertices[i].y ;
            float z = mesh->mVertices[i].z ;
            coordinate->data.push_back( x );
            coordinate->data.push_back( y );
            coordinate->data.push_back( z );
            
            // texCoordinate
            x = mesh->mTextureCoords[0][i].x;
            y = mesh->mTextureCoords[0][i].y;
            texCoordinate->data.push_back( x );
            texCoordinate->data.push_back( y );

            // normal
            x = mesh->mNormals[i].x;
            y = mesh->mNormals[i].y;
            z = mesh->mNormals[i].z;
            normal->data.push_back( x );
            normal->data.push_back( y );
            normal->data.push_back( z );

            // tangent
            x = mesh->mTangents[i].x;
            y = mesh->mTangents[i].y;
            z = mesh->mTangents[i].z;
            tangent->data.push_back( x );
            tangent->data.push_back( y );
            tangent->data.push_back( z );
            
            // biTangent
            x = mesh->mBitangents[i].x;
            y = mesh->mBitangents[i].y;
            z = mesh->mBitangents[i].z;
            biTangent->data.push_back( x );
            biTangent->data.push_back( y );
            biTangent->data.push_back( z );
            
        }

        // merge multiple mesh will cause offset 
        unsigned int offset = coordinate->data.size() / coordinate->itemSize;
        for( int i = 0 ; i < mesh->mNumFaces ; ++ i ){
            aiFace face = mesh->mFaces[i];
            for( int j = 0 ; j < face.mNumIndices ; ++ j ){
                index.push_back( face.mIndices[j] + offset );
            }
        }

    };

    std::function< void( aiNode * , const aiScene * ) > parseNode = [&]( aiNode * node , const aiScene * scene ){
        
        unsigned int subNodeNumber = node->mNumChildren;
        unsigned int subMeshNumber = node->mNumMeshes;

        for( int i = 0 ; i < subMeshNumber ; ++ i ){
            parseMesh( scene->mMeshes[ node->mMeshes[i] ] , scene ) ;
        }

        for( int i = 0 ; i < subNodeNumber ; ++ i ){
            parseNode( node->mChildren[i] , scene );
        }

    };

    parseNode( scene->mRootNode , scene );

    Mesh * mesh = new Mesh();
    mesh->setAttribute( "position" , coordinate );
    mesh->setAttribute( "uv" , texCoordinate );
    mesh->setAttribute( "normal" , normal );
    mesh->setAttribute( "tangent" , tangent );
    mesh->setAttribute( "biTangent" , biTangent );
    
    return mesh;
}



