

out vec4 glFragColor;

in vec3 attr_VertexPosition;

void main(){

    glFragColor = vec4( vec3( gl_FragCoord.z ) , 1.0f );
    // glFragColor = vec4( vec3( 1.0f , 0.0f , 0.0f ) , 1.0f );
    
}