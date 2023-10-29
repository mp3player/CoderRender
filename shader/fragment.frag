// #define _USE_AMBIENT_LIGHT_
// #define _USE_DIRECTION_LIGHT_
// #define _USE_POINT_LIGHT_
// #define _USE_SPOT_LIGHT_

#define PI 3.1415926f;
#include <light>
#include <camera>
// #include <material>

in vec3 depthPosition;

in outAttribute {
    vec3 oPosition;
    vec3 worldPosition;
    vec3 viewPosition;
    vec2 oUv;
    vec3 oNormal;
} vertex ;

layout (binding=0) uniform sampler2D map;
layout (binding=1) uniform sampler2D depthMap;

// multi-light
uniform AmbientLight A_Light0;
uniform DirectionalLight D_Light0;
uniform PointLight P_Light0;
uniform SpotLight S_Light0;

// multi-material
// uniform Material material;

// camera
uniform Camera camera;

uniform mat4 modelMatrix;

out vec4 glFragColor;

in vec3 oTangent;
in vec3 oBiTangent;

void main(){
    glFragColor = vec4( vec3( noise1( vertex.oUv.s ) * .5f + .5f ) , 1.0f );
}