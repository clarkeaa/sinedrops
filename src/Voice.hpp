#pragma once

class MTime;
class Synth;
struct RenderInfo;

class Voice
{
public:
    struct VoiceImpl;

    static Voice* create(Synth* info);

    virtual ~Voice();

    void gateOn(const MTime& time, 
                int key, 
                int velocity);
    
    void gateOff(const MTime& time);
    
    int fillBuffer(const RenderInfo& rinfo);

private:
    Voice(Synth* synth);
    struct VoiceImpl* _impl;
};
