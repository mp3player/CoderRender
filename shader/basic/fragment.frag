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

out vec4 glFragColor ;

void main(){



    vec3 surfaceColor = color;



#ifdef USE_MAP

    surfaceColor *= texture( map , attr_VertexUV ).rgb;

#endif

#ifdef USE_LIGHT

    vec3 normalized_VertexNormal = normalize( attr_VertexNormal );

    vec3 color0 = ambientEffect( ambientLight , surfaceColor );
    vec3 color1 = directionalEffect( directionalLight , surfaceColor , normalized_VertexNormal , mainCamera , attr_VertexPosition );
    vec3 color2 = spotEffect( spotLight , surfaceColor , normalized_VertexNormal , mainCamera , attr_VertexPosition );
    vec3 color3 = pointEffect( pointLight , surfaceColor , normalized_VertexNormal , mainCamera , attr_VertexPosition );

    surfaceColor =   color0 + color1 + color2 + color3 ;

#endif

    glFragColor = vec4( surfaceColor , 1.0f );


}