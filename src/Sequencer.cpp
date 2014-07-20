#include "Sequencer.hpp"
#include <stdint.h>
#include "Voice.hpp"
#include "Instrument.hpp"
#include <cstdlib>
#include <iostream>

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
                       double currentTime)
{
    uint64_t div = currentTime / 0.5;
    if (div > _impl->count) {
        _impl->count = div;

        Voice* voice = instrument->nextVoice();
        int key = rand() % 5 * 12;
        voice->gateOn(key, 60);
        std::cout << "gateOn " << this << " " << key << std::endl;
    }
}
