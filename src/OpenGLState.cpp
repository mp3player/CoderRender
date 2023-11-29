#include <core/OpenGLState.hpp>


void OpenGLState::enable( GLenum capability ){
    glEnable( capability );
}

void OpenGLState::disable( GLenum capability ){
    glDisable( capability );
}

void OpenGLState::clear( unsigned int mask ){
    glClear( mask );
}

void OpenGLState::blendColor( float r , float g , float b , float a ){
    this->_BlendColor = glm::vec4( r , g , b , a );
    glBlendColor( r , g , b, a );
}

void OpenGLState::blendEquation( GLenum mode ){
    glBlendEquation( mode );
}

void OpenGLState::blendEquationi( unsigned int buff , GLenum mode ){
    glBlendEquationi( buff , mode );
}

void OpenGLState::blendFunc( GLenum sFactor , GLenum tFactor ){
    glBlendFunc( sFactor , tFactor );
}

void OpenGLState::blendFunci( unsigned int buff , GLenum sFactor , GLenum tFactor ){
    glBlendFunci( buff , sFactor , tFactor );
}

void OpenGLState::colorMask( float r , float g , float b , float a ){
    glColorMask( r , g , b , a );
}

void OpenGLState::colorMaski( unsigned int buff , float r , float g , float b , float a ){
    glColorMaski( buff , r , g , b , a );
}

void OpenGLState::frontFace( GLenum mode ){
    glFrontFace( mode );
}

void OpenGLState::cullFace( GLenum mode ){
    glCullFace( mode );
}

void OpenGLState::depthFunc( GLenum func ){
    glDepthFunc( func );
}

void OpenGLState::depthMask( unsigned char flag ){
    glDepthMask( flag );
}

void OpenGLState::depthRange( double near , double far ){
    glDepthRange( near , far );
}

void OpenGLState::depthRangef( float near , float far ){
    glDepthRangef( near , far );
}

void OpenGLState::getBooleanv( GLenum pname , unsigned char * data ){
    glGetBooleanv( pname , data );
}

void OpenGLState::getDoublev( GLenum pname , double * data ){
    glGetDoublev( pname , data );
}

void OpenGLState::getFloatv( GLenum pname , float * data ){
    glGetFloatv( pname , data );
}

void OpenGLState::getIntegerv( GLenum pname , int * data ){
    glGetIntegerv( pname , data );
}

GLenum OpenGLState::getError(){
    return glGetError();
}

void OpenGLState::hint( GLenum target , GLenum mode ){
    glHint( target , mode );
}

unsigned char OpenGLState::isEnabled( GLenum capability ){
    return glIsEnabled( capability );
}

void OpenGLState::lineWidth( int width ){
    glLineWidth( width );
}

void OpenGLState::logicOp( GLenum opcode ){
    glLogicOp( opcode );
}

void OpenGLState::pixelStoref( GLenum pname , float param ){
    glPixelStoref( pname , param );
}

void OpenGLState::pixelStorei( GLenum pname , int param ){
    glPixelStorei( pname , param );
}

void OpenGLState::pointParameterf( GLenum pname , float param ){
    glPointParameterf( pname , param );
}

void OpenGLState::pointParameteri( GLenum pname , int param ){
    glPointParameteri( pname , param );
}

void OpenGLState::pointSize( int size ){
    glPointSize( size );
}

void OpenGLState::polygonMode( GLenum face , GLenum mode ){
    glPolygonMode( face , mode );
}

void OpenGLState::polygonOffset( float factir , float units ){
    glPolygonOffset( factir , units );
}

void OpenGLState::samplerCoverage( float value , unsigned char invert ){
    glSampleCoverage( value , invert );
}

void OpenGLState::scissor( float x , float y , float width , float height ){
    glScissor( x , y , width , height );
}

void OpenGLState::stencilFunc( GLenum func , int ref , unsigned int mask ){
    glStencilFunc( func , ref , mask );
}

void OpenGLState::stencilMask( unsigned int mask ){
    glStencilMask( mask );
}

void OpenGLState::stencilOp( GLenum sFail , GLenum dpfail , GLenum dppass ){
    glStencilOp( sFail , dpfail , dppass );
}

void OpenGLState::viewport( int x , int y , int width , int height ){
    glViewport( x , y , width , height );
}

void OpenGLState::bindVertexArray( unsigned int vao ){
    glBindVertexArray( vao );
}

void OpenGLState::bindBuffer( GLenum target , unsigned int buff ){
    glBindBuffer( target , buff );
}

void OpenGLState::bindTexture( GLenum target , unsigned int texture ){
    glBindTexture( target , texture );
}


