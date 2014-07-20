#include "SineVoice.hpp"
#include <cstdio>
#include <cstring>

static const int s_numChannels = 2;

void SineVoice::gateOn(int key, int velocity)
{

}

void SineVoice::gateOff()
{

}

int SineVoice::fillBuffer(float* buffer,
                          unsigned long frameCount, 
                          double currentTime)
{
    memset(buffer, 0, frameCount*s_numChannels*sizeof(float));
    return 0;
}
