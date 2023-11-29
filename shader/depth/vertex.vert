#include <camera>

layout( location = 0 ) in vec3 position;

uniform mat4 modelMatrix;
uniform Camera mainCamera;

out vec3 attr_VertexPosition;


void main(){

    gl_Position = mainCamera.viewProjectionMatrix * modelMatrix * vec4( position , 1.0f );

    attr_VertexPosition = ( modelMatrix * vec4( position , 1.0f ) ).xyz;


}