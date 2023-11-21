#include<light>


in vec3 attr_VertexPosition;
in vec2 attr_VertexUV;
in vec3 attr_VertexNormal;


uniform vec3 color ;


#ifdef USE_MAP
    uniform sampler2D map;
#endif

#ifdef USE_LIGHT
    uniform AmbientLight ambientLight;
    uniform DirectionalLight directionalLight;
#endif

out vec4 glFragColor ;

void main(){



    vec3 surfaceColor = color;



#ifdef USE_MAP
    surfaceColor *= texture( map , attr_VertexUV ).rgb;

#endif

#ifdef USE_LIGHT


    vec3 normal = normalize( attr_VertexNormal );

    vec3 color0 = ambientEffect( ambientLight , surfaceColor );
    vec3 color1 = directionalEffect( directionalLight , normal , surfaceColor );
    surfaceColor = color0 + color1;

#endif


    glFragColor = vec4( directionalLight.direction , 1.0f );

}