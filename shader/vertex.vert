#include <camera>

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 uv;
layout ( location = 2 ) in vec3 normal;

#ifndef USE_NORMAL_MAP

layout ( location = 3 ) in vec3 tangent;
layout ( location = 4 ) in vec3 biTangent;

#endif

out outAttribute {
    vec3 oPosition;
    vec3 worldPosition;
    vec3 viewPosition;
    vec2 oUv;
    vec3 oNormal;
} vertex ;

uniform mat4 modelMatrix;
uniform Camera camera;
uniform Camera shadowCamera;

out vec3 depthPosition;

out vec3 oTangent;
out vec3 oBiTangent;

void main(){
    
    gl_Position = camera.viewProjectionMatrix * modelMatrix * vec4( position , 1.0f );


    vertex.oPosition = position;
    vertex.worldPosition = ( modelMatrix * vec4( position , 1.0f ) ).xyz;
    vertex.viewPosition = ( camera.viewMatrix * vec4( vertex.worldPosition , 1.0f ) ).xyz;
    vertex.oUv = uv;
    vertex.oNormal = mat3( modelMatrix ) * normal;
    depthPosition = .5f * ( shadowCamera.viewProjectionMatrix * modelMatrix * vec4( position , 1.0f )).xyz + .5f ;

    oTangent = tangent;
    oBiTangent = biTangent;
}