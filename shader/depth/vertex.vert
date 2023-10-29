#include <camera>

layout( location = 0 ) in vec2 position;
layout( location = 1 ) in vec2 uv;
layout( location = 2 ) in vec3 normal;

uniform mat4 modelMatrix;
uniform Camera camera;

out vec3 oPosition;
out vec2 oUv;
out vec3 oNormal;

void main(){

    gl_Position = vec4( position * .9f , 0.0f , 1.0f );

    oPosition = vec3( position , 0.0f );
    oUv = uv;
    oNormal = normal;

}