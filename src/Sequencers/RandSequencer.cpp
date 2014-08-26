#include "RandSequencer.hpp"
#include <stdint.h>
#include "Voice.hpp"
#include "Instrument.hpp"
#include <cstdlib>
#include <iostream>
#include "MTime.hpp"

struct RandSequencer::RandSequencerImpl {
    uint64_t count;
    int voiceCount;

    RandSequencerImpl()
        : count(0), 
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
    uint64_t div = currentTime.seconds() / 0.125;
    if (div > _impl->count) {
        _impl->count = div;

        Voice* lastVoice = instrument->getVoice(_impl->voiceCount++);

        if (lastVoice) {
            lastVoice->gateOff(currentTime);
        }

        if (div % 16 == 0) {
            Voice* nextVoice = instrument->nextVoice(_impl->voiceCount);
            int key = ((rand() % 20) + 10) * 3;
            nextVoice->gateOn(currentTime, key, 60);
        }
    }
}

void RandSequencer::run() 
{
    std::cout << "press enter key..." << std::endl;
    int inchar = getchar();
    (void)inchar;
}

