#pragma once

class MTime;

class SineDrops
{
public:
    struct SineDropsImpl;

    static SineDrops* create(int channelCount, 
                             double sampleRate);

    virtual ~SineDrops();

    int fillBuffer(float* buffer, 
                   unsigned long frameCount, 
                   const MTime& currentTime);
    
private:
    SineDrops(int channelCount, 
              double sampleRate);
    
    struct SineDropsImpl* _impl;
};
