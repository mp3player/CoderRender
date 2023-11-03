
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;


uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewProjectionMatrix;


void main(){
    gl_Position = projectionMatrix * viewMatrix  * vec4( position / 2.0f, 1.0f );
}