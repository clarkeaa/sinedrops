#include "SineDrops.hpp"
#include <string.h>
#include "Sequencer.hpp"
#include "Instrument.hpp"
#include "VoiceFactory.hpp"
#include "SineVoice.hpp"

struct SineDrops::SineDropsImpl {
    int channelCount;
    double sampleRate;
    Instrument* instrument;
    Sequencer* sequencer;

    SineDropsImpl(int pchannelCount, 
		  double psampleRate)
	: channelCount(pchannelCount),
	  sampleRate(psampleRate) {}
};

SineDrops* SineDrops::create(int channelCount, 
			     double sampleRate)
{
    return new SineDrops(channelCount, sampleRate);
}

namespace {
    class SineFactory : public VoiceFactory {
        Voice* makeVoice() {
            return SineVoice::create();
        }
    };
}

SineDrops::SineDrops(int channelCount, 
                     double sampleRate)
    : _impl(new SineDropsImpl(channelCount, sampleRate))
{
    SineFactory vfactory;
    _impl->instrument = Instrument::create(4, &vfactory);
    _impl->sequencer = Sequencer::create();
}

SineDrops::~SineDrops()
{
    delete _impl->instrument;
    delete _impl->sequencer;
    delete _impl;
}

int SineDrops::fillBuffer(float* buffer, 
			  unsigned long frameCount, 
			  double currentTime)
{
    _impl->sequencer->update("sine", _impl->instrument, currentTime);    
    _impl->instrument->fillBuffer(buffer, frameCount, currentTime);
    return 0;
}
