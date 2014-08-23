
#pragma once

#include "Effect.hpp"

class Delay : public Effect
{
public:
    struct DelayImpl;
    
    Delay(const MTime& duration,
          float wetDry,
          float feedBack);

    virtual ~Delay();

    virtual int fillBuffer(float* buffer, 
                           unsigned long frameCount, 
                           const MTime& currentTime) override;
    
private:
    DelayImpl* _impl;
};
