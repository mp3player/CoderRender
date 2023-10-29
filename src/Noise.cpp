#include <math/noise.hpp>


float PerlinNoise::octave = 8.0f;

float frac( float value ){
    std::ceil( value ) - value;
}


glm::vec2 PerlinNoise::rand( float x , float y ){

    float z = (2920 << 2) * x * 21942 + y * 171324 + 8912 * x * 23157 * y * 217832 * 9758;
    
    return glm::vec2( cos( z ) , sin( z ) );
}

float PerlinNoise::smooth( float x ){
    return 3.0f * std::pow( x , 2.0f ) - 2.0f * pow( x , 3.0f );
}

float PerlinNoise::noise( float x ){

    return PerlinNoise::noise( x , 0.0f );
}

float PerlinNoise::noise( float x , float y ){
    float octave = PerlinNoise::octave;
    // 1、 generate random vector 
    int x0 = int( x / octave );
    int x1 = x0 + 1;

    int y0 = int( y / octave );
    int y1 = y0 + 1;

    glm::vec2 p = glm::vec2( x , y );

    glm::vec2 v0 = PerlinNoise::rand( x0 , y0 );
    glm::vec2 v1 = PerlinNoise::rand( x1 , y0 );
    glm::vec2 v2 = PerlinNoise::rand( x0 , y1 );
    glm::vec2 v3 = PerlinNoise::rand( x1 , y1 );

    glm::vec2 g0 = glm::vec2( x0 , y0 );
    glm::vec2 g1 = glm::vec2( x1 , y0 );
    glm::vec2 g2 = glm::vec2( x0 , y1 );
    glm::vec2 g3 = glm::vec2( x1 , y1 );

    glm::vec2 o0 = ( p / octave - g0 );
    glm::vec2 o1 = ( p / octave - g1 );
    glm::vec2 o2 = ( p / octave - g2 );
    glm::vec2 o3 = ( p / octave - g3 );

    float s = glm::dot( o0 , v0 );
    float t = glm::dot( o1 , v1 );
    float u = glm::dot( o2 , v2 );
    float v = glm::dot( o3 , v3 );

    float fx = PerlinNoise::smooth( o0.x );
    float fy = PerlinNoise::smooth( o0.y );

    float dx = s + ( t - s ) * fx;
    float dy = u + ( v - u ) * fx;

    return dx + ( dy - dx ) * fy;

}
