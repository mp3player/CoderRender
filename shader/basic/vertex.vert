
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec3 v3Position;
out vec2 v2Uv;


uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

uniform mat3 normalMatrix;
uniform mat4 mvp;


void main(){
    gl_Position =  viewProjectionMatrix * modelMatrix * vec4( position, 1.0f );
    v2Uv = uv;
}