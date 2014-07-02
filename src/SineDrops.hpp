#pragma once

class SineDrops
{
public:
    struct SineDropsImpl;

    static SineDrops* create(int channelCount, 
			     double sampleRate);

    virtual ~SineDrops();

    int fillBuffer(float* buffer, unsigned long frameCount);

private:
    SineDrops(int channelCount, 
	      double sampleRate);

    struct SineDropsImpl* _impl;
};
