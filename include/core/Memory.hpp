#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

#include <vector>

template< typename T >
struct Memory{

    std::vector< T * > buffers;

    public:
        Memory() = default;
        ~Memory();

    public:
        void dispose();
        // check the reference count
        void update();


};  


#endif 