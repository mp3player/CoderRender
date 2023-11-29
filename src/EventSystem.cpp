#include <system/EventSystem.hpp>

/*
void MouseEventHandler(GLFWwindow* window, int button, int action, int mods){

    if( action == MOUSEDOWN ) {
        btn = button;
        mouseDown = true;
        double x , y ;
        glfwGetCursorPos( window , &x , &y );
        position = glm::vec2( x , y );
    }else {
        mouseDown = false;
        btn = -1;
    }
    // action => 1 down , 0 up
    // button => 0 left , 1 right , 2 middle

};

void KeyEventHandler( GLFWwindow* window, int key, int scancode, int action, int mods ){

    // action => 1 down , 0 up
    // key => keyCode
    // w : 87 , s : 83 , a : 65 , d : 68



    if( mainCamera == nullptr ) return ;

    Transform * t = mainCamera->getComponent< Transform >();

    if( t == nullptr ) return ;

    if( action == 1 ){
        switch( key ){
            case UP : { t->translate( 0 , 1 , 0 ); }break;
            case DOWN : { t->translate( 0 , -1 , 0 ); }break;
            case LEFT : { t->translate( -1 , 0 , 0 ); }break;
            case RIGHT : { t->translate( 1 , 0 , 0 ); }break;
            case SPACE : { 
                t->setTranslation( glm::vec3( 0 , 0 , 4 ) );
                t->setRotation( glm::vec3( 0 , 0 ,0 ) ) ;
            }break;
            default : {}break;
        }
    }

}

void ScrollEventHandler( GLFWwindow* window, double xoffset, double yoffset ){
    
    if( mainCamera == nullptr ) return ;

    Transform * transform = mainCamera->getComponent< Transform >();

    glm::vec3 lookAt = transform->v3LookAt;

    glm::vec3 direction = glm::normalize( transform->v3LookAt - transform->v3Translation );

    direction.x *= yoffset;
    direction.y *= yoffset;
    direction.z *= yoffset;

    glm::vec3 position = glm::normalize( direction ) + transform->v3Translation;

    transform->setTranslation( position );

}

void MouseMoveHandler(GLFWwindow* window, double xpos, double ypos){

    if( mouseDown && mainCamera != nullptr ){


        
    }
    
}

*/