struct AmbientLight {
    vec3 color;
    float intensity;
};

struct DirectionalLight {
    vec3 color;
    float intensity;
    vec3 direction;
};

vec3 ambientEffect( in AmbientLight light , in vec3 surfaceColor ){
    return light.color * light.intensity * surfaceColor;
}


vec3 directionalEffect( in DirectionalLight light , in vec3 normal , in vec3 surfaceColor ){
    float weight = max( 0.0f , dot( light.direction , normal ) );
    return weight * light.color * light.intensity * surfaceColor;
}

