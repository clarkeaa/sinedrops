#pragma once

class MTime;
class Synth;

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
    
    int fillBuffer(float* buffer, 
                   unsigned long frameCount, 
                   const MTime& currentTime);

private:
    Voice(Synth* synth);
    struct VoiceImpl* _impl;
};
