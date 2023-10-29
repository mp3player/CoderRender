#ifndef _REF_HPP_
#define _REF_HPP_

struct Ref {

    protected :
        int * iReferenceCount;
    
    public:
        Ref();
        explicit Ref( const Ref & ref );
        virtual ~Ref();

    protected:
        virtual void release();
        
};


#endif