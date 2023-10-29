
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;


uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewProjectionMatrix;

uniform float time;

void main(){
    gl_Position =  mat4( 
        cos(time ) , sin( time ) , 0 , 0 ,
        -sin( time ) , cos( time) , 0 , 0 ,
        0 , 0 , 1 , 0 ,
        0 , 0 , 0, 1 ) * vec4( position , 1.0f );
}