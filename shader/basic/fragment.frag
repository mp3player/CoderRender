#include <light>

out vec4 glFragColor ;

uniform AmbientLight ambientLight_0;
uniform AmbientLight ambientLight_1;

uniform DirectionalLight directionalLight_0;
uniform DirectionalLight directionalLight_1;

const vec3 surfaceColor = vec3( 1.0f , 1.0f , 1.0f );


void main(){
    
    vec3 color = ambientEffect( ambientLight_0 , surfaceColor );

    glFragColor = vec4( color ,1.0f );

}