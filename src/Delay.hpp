
#pragma once

class MTime;

class Delay
{
public:
    struct DelayImpl;
    
    Delay(const MTime& duration,
          float wetDry,
          float feedBack);

    virtual ~Delay();

    int fillBuffer(float* buffer, 
                   unsigned long frameCount, 
                   const MTime& currentTime);
    
private:
    DelayImpl* _impl;
};
