struct AmbientLight {
    vec3 color;
};

struct DirectionalLight {
    vec3 color;
    vec3 direction;
};

vec3 ambientEffect( in AmbientLight light , in vec3 surfaceColor ){
    return light.color * surfaceColor;
}


vec3 directionalEffect( in DirectionalLight light , in vec3 normal , in vec3 surfaceColor ){
    float weight = max( 0.0f , dot( normalize( light.direction ) , normal ) );
    return weight * light.color * surfaceColor;
}

