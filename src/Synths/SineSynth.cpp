
#include "SineSynth.hpp"

#include <cmath>
#include "Envelope.hpp"
#include "GateInfo.hpp"
#include "RenderOptions.hpp"
#include <cassert>
#include "RenderInfo.hpp"

static double chromatic(int key)
{
    return pow(2.0, (key + 48) / 12.0);
}

SineSynth::SineSynth()
    : _scale(chromatic),
      _envelope(NULL)
{
    
}

SineSynth::~SineSynth()
{
    safeRelease(_envelope);
}

void SineSynth::setEnvelope(Envelope* envelope)
{
    set(&_envelope, envelope);    
}
    
Envelope* SineSynth::envelope()
{
    return _envelope;
}

void SineSynth::setScale(const ScaleFunc& scaleFunc)
{
    _scale = scaleFunc;
}

const Synth::ScaleFunc& SineSynth::scale() const
{
    return _scale;
}

int SineSynth::fillBuffer(const RenderInfo& rinfo,
                          double freq,
                          double amp,
                          const GateInfo& gateOnInfo,
                          const GateInfo& gateOffInfo)
{
    float* buffer = rinfo.buffer;
    uint64_t countStart = rinfo.currentTime.value;
    double sinCo = freq * 2.0 * M_PI / kSampleRate;
    MTime envTime = rinfo.currentTime;
    for(int i=0; i<rinfo.frameCount; ++i) {
        envTime.value = rinfo.currentTime.value + i;
        double envAmp = Envelope::calc(_envelope,
                                       gateOnInfo,
                                       gateOffInfo,
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
