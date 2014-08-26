#pragma once

class MTime;
struct RenderInfo;
class Sequencer;

class SineDrops
{
public:
    struct SineDropsImpl;

    static SineDrops* create(int channelCount, 
                             double sampleRate);

    virtual ~SineDrops();

    int fillBuffer(const RenderInfo& rinfo);

    Sequencer* sequencer();
    
private:
    SineDrops(int channelCount, 
              double sampleRate);
    
    struct SineDropsImpl* _impl;
};
