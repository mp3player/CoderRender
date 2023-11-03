#ifndef _MANAGER_MEMORY_HPP_
#define _MANAGER_MEMORY_HPP_

#include <vector>

template< typename T >
struct MemoryManager {
    
    private:

        std::vector< T * > _ptrs ;
        bool disposed = false;

    public:

        MemoryManager() = default;
        ~MemoryManager();

    public:

        void add( T * t );
    
    public:

        void clear();
        void dispose();

        void update();


};

template<typename T>
MemoryManager<T>::~MemoryManager(){
    this->dispose();
    this->clear();
}

template< typename T>
void MemoryManager<T>::add( T * t ){
    this->_ptrs.push_back( t );
}

template< typename T >
void MemoryManager<T>::clear(){

    if( !this->disposed ){
        this->dispose();
    }

    this->_ptrs.clear();

}

template< typename T>
void MemoryManager<T>::dispose(){

    typedef T* Type;

    for( Type & t : this->_ptrs ){
        delete t;
        t = nullptr;
    }

    this->disposed = true;

}

template< typename T >
void MemoryManager<T>::update(){
    // auto release => reference count;
}

#endif