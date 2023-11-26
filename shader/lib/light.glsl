struct AmbientLight {
    vec3 color;
};

struct DirectionalLight {
    vec3 color;
    vec3 direction;
};

struct SpotLight {
    vec3 color;
    vec3 position;
    vec3 direction;
    float intensity;
    float cutOff;
};

struct PointLight {
    vec3 color;
    float intensity;
    vec3 position;
};



vec3 ambientEffect( in AmbientLight light , in vec3 surfaceColor ){
    return light.color * surfaceColor;
}


vec3 directionalEffect( in DirectionalLight light , in vec3 surfaceColor , in vec3 normal , in Camera camera , in vec3 position ){
    
    float diffuse = max( 0.0f , dot( normalize( -light.direction ) , normal ) );

    if( diffuse > 0.0f ){
        vec3 direction = normalize( reflect( light.direction , normal ) );

        vec3 view = normalize( camera.position - position );


        diffuse += pow( max( 0.0f , dot( direction , view ) ) , 32.0f );
    }

    

    return diffuse * light.color ;

}


vec3 spotEffect( in SpotLight light , in vec3 surfaceColor , in vec3 normal , in Camera camera , in vec3 position ){

    vec3 view = normalize( position - light.position );

    float diffuse = max( 0.0f , dot( -view , normal ) );

    if( diffuse <= 0.0f ) {
        return vec3( 0.0f );
    }

    float theta = dot( light.direction , view );

    if( theta > light.cutOff ){
        view = position - light.position;
        float dist = dot( view , view );
        return surfaceColor * diffuse * light.color * light.intensity / dist  ;
    }

    return vec3( 0.0f );

}


vec3 pointEffect( in PointLight light , in vec3 surfaceColor , in vec3 normal , in Camera camera , in vec3 position ){

    vec3 lightView = position - light.position ;

    float dist = dot( lightView , lightView );

    lightView = normalize( lightView );

    vec3 cameraView = normalize( position - camera.position );
    
    float diffuse = max( 0.0f , dot( -lightView , normal ) );

    if( diffuse > 0.0f ){
        diffuse += max( 0.0f , dot( reflect( lightView , normal ) , -cameraView ) );
    }

    


    return surfaceColor * ( diffuse ) * light.color * light.intensity / dist ;

}
