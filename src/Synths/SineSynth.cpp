
#include "SineSynth.hpp"

#include <cmath>
#include "Envelope.hpp"
#include "GateInfo.hpp"
#include "RenderOptions.hpp"
#include <cassert>
#include "RenderInfo.hpp"
#include "AREnvelope.hpp"

static double chromatic(int key)
{
    return pow(2.0, (key + 48) / 12.0);
}

SineSynth::SineSynth()
    : _scale(chromatic),
      _ampEnvelope(NULL)
{
    AREnvelope* env = new AREnvelope();
    env->setAttack(0.01)
        .setRelease(1.0);
    _ampEnvelope = env;
    _ampEnvelope->retain();
}

SineSynth::~SineSynth()
{
    safeRelease(_ampEnvelope);
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
    double sinCo = freq * 2.0 * M_PI / kSampleRate;
    MTime loopTime = rinfo.currentTime;
    for(int i=0; i<rinfo.frameCount; ++i) {
        loopTime.value = rinfo.currentTime.value + i;
        double envAmp = Envelope::calc(_ampEnvelope,
                                       gateOnInfo,
                                       gateOffInfo,
                                       loopTime);
        float val = amp * envAmp * sin(sinCo * loopTime.value);

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
