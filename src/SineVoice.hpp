#pragma once

#include "Voice.hpp"
#include "MTime.hpp"

class SineVoice : public Voice
{
public:
    struct SineVoiceImpl;

    static SineVoice* create();

    virtual ~SineVoice();

    virtual void gateOn(const MTime& time, 
                        int key, 
                        int velocity);

    virtual void gateOff(const MTime& time);
    
    virtual int fillBuffer(float* buffer, 
                           unsigned long frameCount, 
                           const MTime& currentTime);
private:
    SineVoice();
    struct SineVoiceImpl* _impl;
};
