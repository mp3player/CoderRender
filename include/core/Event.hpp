#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include <core/EventListener.hpp>

struct Event {

    enum EventType {
        UNKNOW , 
        MOUSE_DOWN , MOUWE_UP , MOUSE_MOVE , MOUSE_ENTER , MOUSE_LEAVE , 
        KEY_DOWN , KEY_UP 
    };

    EventType eventType;
    
    float x ;
    float y ;


};


#endif