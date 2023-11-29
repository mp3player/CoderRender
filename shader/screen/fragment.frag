in vec2 oUv;

uniform sampler2D map;

out vec4 glFragColor ;


void main(){
    vec3 color = texture( map , oUv ).rgb ;
    glFragColor = vec4( color + .1f , 1.0f );
}