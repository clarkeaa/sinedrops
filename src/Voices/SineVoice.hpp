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
                        int velocity) override;

    virtual void gateOff(const MTime& time) override;
    
    virtual int fillBuffer(float* buffer, 
                           unsigned long frameCount, 
                           const MTime& currentTime) override;
private:
    SineVoice();
    struct SineVoiceImpl* _impl;
};
