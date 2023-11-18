
layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

out vec3 v3Position;
out vec3 v3Normal;


uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

uniform mat3 normalMatrix;
uniform mat4 mvp;


void main(){
    gl_Position =  viewProjectionMatrix * modelMatrix * vec4( position, 1.0f );
    v3Position = position;
    v3Normal = normalMatrix * normal;
}