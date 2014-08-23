
#include "Object.hpp"

Object::Object()
    : _refCount(0)
{

}

Object::~Object() 
{

}

void Object::retain()
{
    _refCount += 1;
}

void Object::release()
{
    _refCount -= 1;
    if (_refCount <= 0) {
        delete this;
    }
}

