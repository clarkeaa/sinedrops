
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

    virtual int fillBuffer(const RenderInfo& rinfo) override;
    
private:
    DelayImpl* _impl;
};
