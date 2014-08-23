
#pragma once

class MTime;

class Effect
{
public:
    virtual ~Effect() {}

    virtual int fillBuffer(float* buffer, 
                           unsigned long frameCount, 
                           const MTime& currentTime) =0;
};
