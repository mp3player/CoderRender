struct AmbientLight {
    vec3 color;
    float intensity;
};

struct DirectionalLight {
    vec3 color;
    float intensity;
    vec3 direction;
};

struct PointLight {
    vec3 color ; 
    float intensity ;
    vec3 position;
    float strength;
};

struct SpotLight {
    vec3 color;
    float intensity;
    vec3 position;
    vec3 lookAt;
    float range;
    float strength;
};