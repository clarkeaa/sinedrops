#include "SineDrops.hpp"
#include <string.h>
#include "Sequencer.hpp"
#include "Instrument.hpp"

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

SineDrops::SineDrops(int channelCount, 
		     double sampleRate)
    : _impl(new SineDropsImpl(channelCount, sampleRate))
{
    _impl->instrument = Instrument::create();
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

    memset(buffer, 
	   0, 
	   sizeof(float) * _impl->channelCount * frameCount);

    return 0;
}
