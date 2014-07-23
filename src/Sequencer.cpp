#include "Sequencer.hpp"
#include <stdint.h>
#include "Voice.hpp"
#include "Instrument.hpp"
#include <cstdlib>
#include <iostream>
#include "MTime.hpp"

struct Sequencer::SequencerImpl {
    uint64_t count;

    SequencerImpl()
        : count(0)
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
    uint64_t div = currentTime.seconds() / 0.25;
    if (div > _impl->count) {
        _impl->count = div;

        Voice* voice = instrument->nextVoice();
        int key = ((rand() % 20) + 10) * 3;
        voice->gateOn(key, 60);
    }
}
