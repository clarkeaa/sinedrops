#include "Instrument.hpp"
#include <cstdlib>
#include <cstring>
#include <vector>
#include "Voice.hpp"
#include "VoiceFactory.hpp"

static const int s_numChannels = 2;

struct Instrument::InstrumentImpl {
    std::vector<Voice*> voices;
    std::vector<uint32_t> voiceIdents;
    int currentIndex;

    InstrumentImpl(int polyphony)
        : voices(polyphony),
          voiceIdents(polyphony, 0),
          currentIndex(0)
        {}
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

static void mix(float* dst, float* src, unsigned long frameCount)
{
    unsigned long count = frameCount * s_numChannels;
    unsigned long n = (count + 7) / 8;
    switch(count % 8) {
    case 0:do {*dst++ += *src++;
        case 7:*dst++ += *src++;
        case 6:*dst++ += *src++;
        case 5:*dst++ += *src++;
        case 4:*dst++ += *src++;
        case 3:*dst++ += *src++;
        case 2:*dst++ += *src++;
        case 1:*dst++ += *src++;
        } while(--n > 0);
    }
}

int Instrument::fillBuffer(float* buffer, 
                           unsigned long frameCount, 
                           const MTime& currentTime)
{
    memset(buffer, 0, frameCount*s_numChannels*sizeof(float));
    float tempBuffer[frameCount*s_numChannels];
    for( auto voice : _impl->voices) {
        voice->fillBuffer(tempBuffer, frameCount, currentTime);
        mix(buffer, tempBuffer, frameCount);
    }
    
    return 0;
}
