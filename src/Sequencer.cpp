#include "Sequencer.hpp"
#include <stdint.h>
#include "Voice.hpp"
#include "Instrument.hpp"
#include <cstdlib>
#include <iostream>
#include "MTime.hpp"

struct Sequencer::SequencerImpl {
    uint64_t count;
    Voice* lastGateOnVoice;

    SequencerImpl()
        : count(0), 
          lastGateOnVoice(NULL)
        {}
};

Sequencer* Sequencer::create()
{
    return new Sequencer();
}

Sequencer::Sequencer()
    : _impl(new SequencerImpl())
{
}

Sequencer::~Sequencer()
{
    delete _impl;
}

void Sequencer::update(const std::string& name, 
                       Instrument* instrument,
                       const MTime& currentTime)
{
    uint64_t div = currentTime.seconds() / 0.5;
    if (div > _impl->count) {
        _impl->count = div;

        Voice* voice = instrument->nextVoice();

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
