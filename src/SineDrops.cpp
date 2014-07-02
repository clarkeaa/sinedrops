#include "SineDrops.hpp"
#include <string.h>

struct SineDrops::SineDropsImpl {
    int channelCount;
    double sampleRate;

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
}

SineDrops::~SineDrops()
{
    delete _impl;
}

int SineDrops::fillBuffer(float* buffer, unsigned long frameCount)
{
    memset(buffer, 
	   0, 
	   sizeof(float) * _impl->channelCount * frameCount);    
    return 0;
}
