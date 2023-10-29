in vec2 oUv;

uniform sampler2D map;

uniform float time;

out vec4 glFragColor ;


void main(){
    vec3 color = texture( map , oUv ).rgb ;
    glFragColor = vec4( color + .1f , 1.0f );
    // glFragColor = texture( map , oUv );
    // glFragColor = vec4( vec3( oUv , 1.0f ) , 1.0f );
}