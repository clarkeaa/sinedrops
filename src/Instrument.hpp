#pragma once

class Voice;
class VoiceFactory;

class Instrument
{
public:
    struct InstrumentImpl;

    static Instrument* create(int polyphony, VoiceFactory* vfactory);

    virtual ~Instrument();

    Voice* nextVoice();

    int fillBuffer(float* buffer, 
                   unsigned long frameCount, 
                   double currentTime);
private:
    Instrument(int polyphony, VoiceFactory* vfactory);

    struct InstrumentImpl* _impl;
};
