
in vec3 v3Normal;

out vec4 glFragColor ;

void main(){
    
    // vec3 surfaceColor = ambientEffect( ambientLight_0 , color );

    glFragColor = vec4( v3Normal ,1.0f );

}