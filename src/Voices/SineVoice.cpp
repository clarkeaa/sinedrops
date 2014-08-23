#include "SineVoice.hpp"

#include <cstdio>
#include <cstring>
#include <cmath>
#include <stdint.h>
#include "Envelope.hpp"
#include <functional>
#include "RenderOptions.hpp"
#include "SineVoiceInfo.hpp"
#include <cassert>

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
    GateInfo gateOnTime;
    GateInfo gateOffTime;
    SineVoiceInfo* info;

    SineVoiceImpl(SineVoiceInfo* argInfo) 
        : key(-1),
          velocity(0),
          info(argInfo)
        {
            info->retain();
        }

    ~SineVoiceImpl() {
        info->release();
    }
};

SineVoice* SineVoice::create(SineVoiceInfo* info)
{
    return new SineVoice(info);
}

SineVoice::SineVoice(SineVoiceInfo* info) 
    : _impl(new SineVoiceImpl(info))
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

static double calcAmpEnv(const Envelope* env,
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
    double freq = _impl->info->scale(_impl->key);
    double amp = calcAmp(_impl->velocity);
    uint64_t countStart = currentTime.value;
    double sinCo = freq * 2.0 * M_PI / kSampleRate;
    MTime envTime = currentTime;
    for(int i=0; i<frameCount; ++i) {
        envTime.value = currentTime.value + i;
        double envAmp = calcAmpEnv(_impl->info->envelope(),
                                   _impl->gateOnTime,
                                   _impl->gateOffTime,
                                   envTime);
        uint64_t count = i + countStart;
        float val = amp * envAmp * sin(sinCo * count);

        switch(kNumChannels) {
        case 2:
            *buffer++ = val;
        case 1:
            *buffer++ = val;
            break;
        default:
            assert(false);
        }
    }

    return 0;
}
