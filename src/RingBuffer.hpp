
#pragma once

#include <stdint.h>
#include <cstdio>

template<typename A>
class RingBuffer
{
public:

    RingBuffer(uint32_t size);

    ~RingBuffer();

    uint32_t read(uint32_t size, A* array);

    uint32_t write(uint32_t size, A* array);

    uint32_t size() const;

private:
    A* _array;
    uint32_t _size;
    uint32_t _readPos;
    uint32_t _writePos;
};

template<typename A>
RingBuffer<A>::RingBuffer(uint32_t size)
    : _array(new A[size]),
      _size(size),
      _readPos(0),
      _writePos(0)
{
    
}

template<typename A>
RingBuffer<A>::~RingBuffer()
{
    if (_array) {
        delete [] _array;
    }
}

template<typename A>
uint32_t RingBuffer<A>::read(uint32_t size, A* array)
{
    for(uint32_t i=0; i < size; ++i) {
        array[i] = _array[_readPos];
        _readPos = (_readPos + 1) % _size;
    }
    return size;
}

template<typename A>
uint32_t RingBuffer<A>::write(uint32_t size, A* array)
{
    for(uint32_t i=0; i < size; ++i) {        
        _array[_writePos] = array[i];
        _writePos = (_writePos + 1) % _size;
    }    
    return size;
}

template<typename A>
uint32_t RingBuffer<A>::size() const
{
    return _size;
}
