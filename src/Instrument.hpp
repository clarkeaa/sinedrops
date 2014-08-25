#pragma once

#include <stdint.h>

class Voice;
class VoiceFactory;
class MTime;
class Effect;
struct RenderInfo;

class Instrument
{
public:
    struct InstrumentImpl;

    static Instrument* create(int polyphony, VoiceFactory* vfactory);

    virtual ~Instrument();

    Voice* getVoice(uint32_t ident);

    Voice* nextVoice(uint32_t ident);

    int fillBuffer(const RenderInfo& renderInfo);
    
    void setEffect(Effect* effect);
    
private:
    Instrument(int polyphony, VoiceFactory* vfactory);

    struct InstrumentImpl* _impl;
};
