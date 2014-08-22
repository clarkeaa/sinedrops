#include "SineVoice.hpp"
#include <cstdio>
#include <cstring>
#include <cmath>
#include <stdint.h>
#include "AREnvelope.hpp"

static const int s_numChannels = 2;
static const double s_sampleRate = 44100.0;

namespace {
    struct GateInfo {
        MTime time;
        bool isSet;
        GateInfo() : time(), isSet(false) {}
        GateInfo(const MTime& argTime) 
            : time(argTime), isSet(true) {}
    };
}

struct SineVoice::SineVoiceImpl {
    int key;
    int velocity;
    AREnvelope* envelope;
    GateInfo gateOnTime;
    GateInfo gateOffTime;

    SineVoiceImpl() 
        : key(-1),
          velocity(0),
          envelope(new AREnvelope())
        {
            envelope->setAttack(0.1)
                .setRelease(0.5);
        }

    ~SineVoiceImpl() {
        delete this->envelope;
    }
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

void SineVoice::gateOn(const MTime& time, int key, int velocity)
{
    _impl->key = key;
    _impl->velocity = velocity;
    _impl->gateOnTime = GateInfo(time);
    _impl->gateOffTime = GateInfo();
}

void SineVoice::gateOff(const MTime& time)
{
    _impl->gateOffTime = GateInfo(time);
}

inline static double calcAmp(int velocity)
{
    return velocity / 127.0f;
}

inline static double calcFreq(int key)
{
    return pow(2.0, (key + 48) / 12.0);
}

static double calcAmpEnv(const AREnvelope* env,
                         const GateInfo& gateOnTime,
                         const GateInfo& gateOffTime,
                         const MTime& currentTime)
{
    if (gateOnTime.isSet) {
        if (gateOffTime.isSet) {
            return env->calc(gateOnTime.time,
                             gateOffTime.time,
                             currentTime);
        } else {
            return env->calc(gateOnTime.time,
                             currentTime);
        }
    } else {
        return 0.0;
    }
}

int SineVoice::fillBuffer(float* buffer,
                          unsigned long frameCount, 
                          const MTime& currentTime)
{
    double freq = calcFreq(_impl->key);
    double amp = calcAmp(_impl->velocity);
    uint64_t countStart = currentTime.value;
    double sinCo = freq * 2.0 * M_PI / s_sampleRate;
    MTime envTime = currentTime;
    for(int i=0; i<frameCount; ++i) {
        envTime.value = currentTime.value + i;
        double envAmp = calcAmpEnv(_impl->envelope,
                                   _impl->gateOnTime,
                                   _impl->gateOffTime,
                                   envTime);
        uint64_t count = i + countStart;
        float val = amp * envAmp * sin(sinCo * count);
        for(int chan=0; chan<s_numChannels; ++chan) {
            *buffer++ = val;
        }
    }

    return 0;
}
