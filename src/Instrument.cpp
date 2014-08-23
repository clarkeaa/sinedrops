#include "Instrument.hpp"

#include "Effect.hpp"
#include "MTime.hpp"
#include "MixTool.hpp"
#include "RenderOptions.hpp"
#include "Voice.hpp"
#include "VoiceFactory.hpp"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <vector>

using MixTool::mix;

struct Instrument::InstrumentImpl {
    std::vector<Voice*> voices;
    std::vector<uint32_t> voiceIdents;
    int currentIndex;
    Effect* effect;

    InstrumentImpl(int polyphony)
        : voices(polyphony),
          voiceIdents(polyphony, 0),
          currentIndex(0),
          effect(NULL)
        {}

    ~InstrumentImpl() {
        if (effect) {
            delete effect;
        }
    }
};

Instrument* Instrument::create(int polyphony, VoiceFactory* vfactory)
{
    return new Instrument(polyphony, vfactory);
}

Instrument::Instrument(int polyphony, VoiceFactory* vfactory)
    : _impl(new InstrumentImpl(polyphony))
{
    for(int i=0; i<polyphony; ++i) {
        _impl->voices[i] = vfactory->makeVoice();
    }
}

Instrument::~Instrument()
{
    for( auto voice : _impl->voices) {
        delete voice;
    }
    delete _impl;
}

Voice* Instrument::getVoice(uint32_t ident)
{
    auto loc = std::find(_impl->voiceIdents.begin(),
                         _impl->voiceIdents.end(),
                         ident);

    Voice* answer = NULL;
    if (loc != _impl->voiceIdents.end()) {
        uint32_t index = loc - _impl->voiceIdents.begin();
        answer = _impl->voices[index];
    } 
    return answer;
}

Voice* Instrument::nextVoice(uint32_t ident)
{
    Voice* answer = getVoice(ident);
    if (!answer) {
        answer = _impl->voices[_impl->currentIndex];
        _impl->voiceIdents[_impl->currentIndex] = ident;
        _impl->currentIndex = 
            (_impl->currentIndex + 1) % _impl->voices.size();
    }
    return answer;
}

int Instrument::fillBuffer(float* buffer, 
                           unsigned long frameCount, 
                           const MTime& currentTime)
{
    memset(buffer, 0, frameCount*kNumChannels*sizeof(float));
    float tempBuffer[frameCount*kNumChannels];
    for( auto voice : _impl->voices) {
        voice->fillBuffer(tempBuffer, frameCount, currentTime);
        mix(buffer, tempBuffer, frameCount*kNumChannels);
    }
    
    if (_impl->effect) {
        _impl->effect->fillBuffer(buffer, frameCount, currentTime);
    }

    return 0;
}

void Instrument::setEffect(Effect* effect)
{
    if (_impl->effect != effect) {
        if (_impl->effect) {
            delete _impl->effect;
        }
        _impl->effect = effect;
    }
}
