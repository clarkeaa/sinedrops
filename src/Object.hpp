#pragma once

class Object
{
public:
    Object();
    
    virtual ~Object();
    
    virtual void retain();

    virtual void release();
    
private:
    int _refCount;
};
