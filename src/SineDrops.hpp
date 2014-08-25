#pragma once

class MTime;
struct RenderInfo;

class SineDrops
{
public:
    struct SineDropsImpl;

    static SineDrops* create(int channelCount, 
                             double sampleRate);

    virtual ~SineDrops();

    int fillBuffer(const RenderInfo& rinfo);
    
private:
    SineDrops(int channelCount, 
              double sampleRate);
    
    struct SineDropsImpl* _impl;
};
