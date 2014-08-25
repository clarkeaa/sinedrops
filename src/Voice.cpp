#include "Voice.hpp"

#include <cstdio>
#include <cstring>
#include <cmath>
#include <stdint.h>
#include "Envelope.hpp"
#include <functional>
#include "RenderOptions.hpp"
#include "Synth.hpp"
#include <cassert>
#include "GateInfo.hpp"
#include "RenderInfo.hpp"

struct Voice::VoiceImpl {
    int key;
    int velocity;
    GateInfo gateOnTime;
    GateInfo gateOffTime;
    Synth* synth;

    VoiceImpl(Synth* argInfo) 
        : key(-1),
          velocity(0),
          synth(argInfo)
        {
            synth->retain();
        }

    ~VoiceImpl() {
        synth->release();
    }
};

Voice* Voice::create(Synth* synth)
{
    return new Voice(synth);
}

Voice::Voice(Synth* synth) 
    : _impl(new VoiceImpl(synth))
{

}

Voice::~Voice() {
    delete _impl;
}

void Voice::gateOn(const MTime& time, int key, int velocity)
{
    _impl->key = key;
    _impl->velocity = velocity;
    _impl->gateOnTime = GateInfo(time);
    _impl->gateOffTime = GateInfo();
}

void Voice::gateOff(const MTime& time)
{
    _impl->gateOffTime = GateInfo(time);
}

inline static double calcAmp(int velocity)
{
    return velocity / 127.0f;
}

int Voice::fillBuffer(const RenderInfo& rinfo)
{
    double freq = _impl->synth->scale()(_impl->key);
    double amp = calcAmp(_impl->velocity);

    return _impl->synth->fillBuffer(rinfo,
                                    freq,
                                    amp,
                                    _impl->gateOnTime,
                                    _impl->gateOffTime);

    return 0;
}
