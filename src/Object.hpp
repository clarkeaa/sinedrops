#pragma once

class Object
{
public:
    Object();
    
    virtual ~Object();
    
    virtual void retain();

    virtual void release();
    
    template<class A>
    static void set(A** oldVal, A* newVal);

    inline static void safeRelease(Object* obj);

private:
    int _refCount;
};

template<class A>
void Object::set(A** pos, A* newVal)
{
    if (*pos != newVal) {
        if (*pos) {
            (*pos)->release();
        }
        *pos = newVal;
        if (*pos) {
            (*pos)->retain();
        }
    }
}

inline void Object::safeRelease(Object* obj)
{
    if (obj) {
        obj->release();
    }
}
