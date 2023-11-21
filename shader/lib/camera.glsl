struct Camera {
    
    mat4 inverseProjectionMatrix;
    mat4 projectionMatrix;

    mat4 inverseViewMatrix;
    mat4 viewMatrix;
    
    mat4 inverseViewProjectionMatrix;
    mat4 viewProjectionMatrix;

    vec3 position;
    vec3 lookAt;

};


// world space to view space
vec3 worldToView( in Camera camera , in vec3 position ){
    return vec4( camera.viewMatrix * vec4( position , 1.0f ) ).xyz ;
}

// view space to world space
vec3 ViewToWorld( in Camera camera , in vec3 position ){
    return vec4( camera.inverseViewMatrix * vec4( position , 1.0f ) ).xyz;
}

