#pragma once

#include "Voice.hpp"

class SineVoice : public Voice
{
public:
    struct SineVoiceImpl;

    static SineVoice* create();

    virtual ~SineVoice();

    virtual void gateOn(int key, int velocity);

    virtual void gateOff();
    
    virtual int fillBuffer(float* buffer, 
                           unsigned long frameCount, 
                           double currentTime);
private:
    SineVoice();
    struct SineVoiceImpl* _impl;
};
