#include "Instrument.hpp"
#include <cstdlib>
#include <cstring>
#include <vector>
#include "Voice.hpp"
#include "VoiceFactory.hpp"
#include "MixTool.hpp"
#include "Delay.hpp"
#include "MTime.hpp"

using MixTool::mix;

static const int s_numChannels = 2;

struct Instrument::InstrumentImpl {
    std::vector<Voice*> voices;
    std::vector<uint32_t> voiceIdents;
    int currentIndex;
    Delay* delay;

    InstrumentImpl(int polyphony)
        : voices(polyphony),
          voiceIdents(polyphony, 0),
          currentIndex(0),
          delay(new Delay({.value=1,.timescale=1}, 0.5, 0.5))
        {}

    ~InstrumentImpl() {
        delete delay;
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
    memset(buffer, 0, frameCount*s_numChannels*sizeof(float));
    float tempBuffer[frameCount*s_numChannels];
    for( auto voice : _impl->voices) {
        voice->fillBuffer(tempBuffer, frameCount, currentTime);
        mix(buffer, tempBuffer, frameCount*s_numChannels);
    }
    
    _impl->delay->fillBuffer(buffer, frameCount, currentTime);

    return 0;
}
