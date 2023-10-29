#include<core/Ref.hpp>
#include <iostream>

Ref::Ref(){
    // std::cout << "start: " << std::endl;
    // std::cout << "constructor : reference count +1" << std::endl;
    iReferenceCount = new int;
    *iReferenceCount = 1;
}

Ref::Ref( const Ref & ref ){
    // std::cout << "copy constructor : reference count +1" << std::endl;
    this->iReferenceCount = ref.iReferenceCount;
    *( this->iReferenceCount ) += 1;
}

Ref::~Ref(){
    // std::cout << "destructor : reference count -1" << std::endl;
    *( this->iReferenceCount ) -= 1;
    if( *( this->iReferenceCount ) <= 0 ) {
        this->release();
    }
}

// Ref& Ref::operator=( const Ref & ref ){
//     std::cout << "assignment : reference count +1" << std::endl;
//     this->iReferenceCount = ref.iReferenceCount ;
//     *( this->iReferenceCount ) += 1;
//     return *this;
// }

void Ref::release(){
    // std::cout << "end: " << std::endl;
    // std::cout << "relase resource : " << *this->iReferenceCount << std::endl;
    delete this->iReferenceCount;
}