#pragma once

class MTime;

class Voice
{
public:
    virtual ~Voice() {}

    virtual void gateOn(const MTime& time, 
                        int key, 
                        int velocity) = 0;

    virtual void gateOff(const MTime& time) = 0;
    
    virtual int fillBuffer(float* buffer, 
                           unsigned long frameCount, 
                           const MTime& currentTime) = 0;
};
