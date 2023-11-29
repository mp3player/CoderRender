#ifndef _OPENGL_STATE_HPP_
#define _OPENGL_STATI_HPP_

#include <glad/glad.h>
#include <glm/glm.hpp>

struct OpenGLState {

    public:

        glm::vec4 _ClearColor = glm::vec4( 0.0f , 0.0f , 0.0f , 1.0f );
        glm::vec4 _BlendColor ;
        glm::vec3 _Viewport ;
        bool _DeepTest = false;
        bool _AlphaTest = false;
        bool _Blend = false;
        bool _ClipDistance = false;
        bool _Dither = false;
        bool _LineSmooth = false;
        bool _MultiSample = false;
        bool _ScissorTest = false;
        bool _StencilTest = false;

        unsigned int blendMode;

    public:

        void enable( GLenum capability );

        void disable( GLenum capability );

        void clear( unsigned int mask );

        void blendColor( float r , float g , float b , float a );

        void blendEquation( GLenum mode );

        void blendEquationi( unsigned int buff , GLenum mode );

        void blendFunc( GLenum sFactor , GLenum tFactor );

        void blendFunci( unsigned int buff , GLenum sFactor , GLenum tFactor );

        void colorMask( float r , float g , float b , float a );

        void colorMaski( unsigned int buff , float r , float g , float b , float a );

        void frontFace( GLenum mode );

        void cullFace( GLenum mode );

        void depthFunc( GLenum func );

        void depthMask( unsigned char flag );

        void depthRange( double near , double far );

        void depthRangef( float near , float far );

        void getBooleanv( GLenum pname , unsigned char * data );

        void getDoublev( GLenum pname , double * data );

        void getFloatv( GLenum pname , float * data );

        void getIntegerv( GLenum pname , int * data );

        GLenum getError();

        void hint( GLenum target , GLenum mode );

        unsigned char isEnabled( GLenum capability );

        void lineWidth( int width );

        void logicOp( GLenum opcode );

        void pixelStoref( GLenum pname , float param );

        void pixelStorei( GLenum pname , int param );

        void pointParameterf( GLenum pname , float param );

        void pointParameteri( GLenum pname , int param );

        void pointSize( int size );

        void polygonMode( GLenum face , GLenum mode );

        void polygonOffset( float factir , float units );

        void samplerCoverage( float value , unsigned char invert );

        void scissor( float x , float y , float width , float height );

        void stencilFunc( GLenum func , int ref , unsigned int mask );

        void stencilMask( unsigned int mask );

        void stencilOp( GLenum sFail , GLenum dpfail , GLenum dppass );

        void viewport( int x , int y , int width , int height );

        void bindVertexArray( unsigned int vao );

        void bindBuffer( GLenum target , unsigned int buff );

        void bindTexture( GLenum target , unsigned int texture );




};


#endif