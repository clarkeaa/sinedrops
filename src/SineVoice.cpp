#include "SineVoice.hpp"
#include <cstdio>
#include <cstring>
#include <cmath>
#include <stdint.h>

static const int s_numChannels = 2;
static const double s_sampleRate = 44100.0;

struct SineVoice::SineVoiceImpl {
    int key;
    int velocity;

    SineVoiceImpl() 
        : key(-1),
          velocity(0)
        {}
};

SineVoice* SineVoice::create()
{
    return new SineVoice();
}

SineVoice::SineVoice() 
    : _impl(new SineVoiceImpl())
{

}

SineVoice::~SineVoice() {
    delete _impl;
}

void SineVoice::gateOn(int key, int velocity)
{
    _impl->key = key;
    _impl->velocity = velocity;
}

void SineVoice::gateOff()
{
    _impl->key = -1;
}

inline static double calcAmp(int velocity)
{
    return velocity / 127.0f;
}

inline static double calcFreq(int velocity)
{
    return pow(2.0, (velocity + 48) / 12.0);
}

int SineVoice::fillBuffer(float* buffer,
                          unsigned long frameCount, 
                          double currentTime)
{
    if (_impl->key < 0 || _impl->velocity <= 0) {
        memset(buffer, 0, frameCount*s_numChannels*sizeof(float));        
    } else {
        double freq = calcFreq(_impl->key);
        double amp = calcAmp(_impl->velocity);
        uint64_t countStart = currentTime * s_sampleRate;
        double sinCo = freq * 2.0 * M_PI / s_sampleRate;
        for(int i=0; i<frameCount; ++i) {
            uint64_t count = i + countStart;
            float val = amp * sin(sinCo * count);
            for(int chan=0; chan<s_numChannels; ++chan) {
                *(++buffer) = val;
            }
        }
    }
    return 0;
}
