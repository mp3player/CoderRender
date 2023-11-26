#include<camera>


layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 attr_VertexPosition;
out vec2 attr_VertexUV;
out vec3 attr_VertexNormal;

uniform Camera mainCamera;
uniform mat4 modelMatrix;

uniform mat3 UVMatrix;
uniform mat3 normalMatrix;
uniform mat4 mvp;


void main(){


    gl_Position = mainCamera.projectionMatrix * mainCamera.viewMatrix * modelMatrix * vec4( position , 1.0f );
    
    attr_VertexPosition = ( modelMatrix * vec4( position , 1.0f ) ).xyz;
    attr_VertexUV = uv;
    attr_VertexNormal = normalMatrix * normal;

}