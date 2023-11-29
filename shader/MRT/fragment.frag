#include<camera>
#include<light>

in vec3 attr_VertexPosition;
in vec2 attr_VertexUV;
in vec3 attr_VertexNormal;


uniform vec3 color ;



#ifdef USE_MAP
    uniform sampler2D map;
#endif

#ifdef USE_LIGHT
    uniform Camera mainCamera;
    uniform AmbientLight ambientLight;
    uniform DirectionalLight directionalLight;
    uniform SpotLight spotLight;
    uniform PointLight pointLight;
#endif


layout( location = 0 ) out vec4 glFragColor ;
layout( location = 1 ) out vec3 normal;

void main(){

    glFragColor = vec3( vec3( 1.0f , 0.0f , 0.0f ) , 1.0f );

}