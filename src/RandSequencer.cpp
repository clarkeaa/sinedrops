#include "RandSequencer.hpp"
#include <stdint.h>
#include "Voice.hpp"
#include "Instrument.hpp"
#include <cstdlib>
#include <iostream>
#include "MTime.hpp"

struct RandSequencer::RandSequencerImpl {
    uint64_t count;
    Voice* lastGateOnVoice;
    int voiceCount;

    RandSequencerImpl()
        : count(0), 
          lastGateOnVoice(NULL),
          voiceCount(0)
        {}
};

RandSequencer* RandSequencer::create()
{
    return new RandSequencer();
}

RandSequencer::RandSequencer()
    : _impl(new RandSequencerImpl())
{
}

RandSequencer::~RandSequencer()
{
    delete _impl;
}

void RandSequencer::update(const std::string& name, 
                           Instrument* instrument,
                           const MTime& currentTime)
{
    uint64_t div = currentTime.seconds() / 0.5;
    if (div > _impl->count) {
        _impl->count = div;

        Voice* voice = instrument->getVoice(_impl->voiceCount++);

        if (voice == _impl->lastGateOnVoice) {
            voice->gateOff(currentTime);
            _impl->lastGateOnVoice = NULL;
        } else {
            int key = ((rand() % 20) + 10) * 3;
            voice->gateOn(currentTime, key, 60);
            if (_impl->lastGateOnVoice) {
                _impl->lastGateOnVoice->gateOff(currentTime);
            }
            _impl->lastGateOnVoice = voice;
        }
    }
}
