#include "SineDrops.hpp"

#include <string.h>
#include "Sequencer.hpp"
#include "Instrument.hpp"
#include "VoiceFactory.hpp"
#include "Voice.hpp"
#include "Delay.hpp"
#include "SineSynth.hpp"
#include "AREnvelope.hpp"
#include "MTime.hpp"
#include "RenderInfo.hpp"

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

namespace {
    class SineFactory : public VoiceFactory {
    public:
        SineFactory() 
            : _sineInfo(new SineSynth())
        {
            _sineInfo->retain();
            AREnvelope* env = new AREnvelope();
            env->setAttack(0.01)
                .setRelease(0.1);
            _sineInfo->setEnvelope(env);
        }
        
        ~SineFactory() {
            _sineInfo->release();
        }
        
        Voice* makeVoice() {
            return Voice::create(_sineInfo);
        }
    private:
        SineSynth* _sineInfo;
    };
}

SineDrops::SineDrops(int channelCount, 
                     double sampleRate)
    : _impl(new SineDropsImpl(channelCount, sampleRate))
{
    SineFactory vfactory;
    int polyphony = 11;
    _impl->instrument = Instrument::create(polyphony, &vfactory);
    _impl->sequencer = Sequencer::create();
    Delay* delay = new Delay({.value=1,.timescale=1}, 0.5, 0.5);
    _impl->instrument->setEffect(delay);
}

SineDrops::~SineDrops()
{
    delete _impl->instrument;
    delete _impl->sequencer;
    delete _impl;
}

int SineDrops::fillBuffer(const RenderInfo& rinfo)
{
    _impl->sequencer->update("sine", 
                             _impl->instrument, 
                             rinfo.currentTime);
    _impl->instrument->fillBuffer(rinfo);
    return 0;
}
