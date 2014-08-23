
#include "SineVoiceInfo.hpp"
#include <cmath>
#include "Envelope.hpp"

static double chromatic(int key)
{
    return pow(2.0, (key + 48) / 12.0);
}

SineVoiceInfo::SineVoiceInfo()
    : scale(chromatic),
      _envelope(NULL)
{
    
}

SineVoiceInfo::~SineVoiceInfo()
{
    safeRelease(_envelope);
}

void SineVoiceInfo::setEnvelope(Envelope* envelope)
{
    set(&_envelope, envelope);    
}
    
Envelope* SineVoiceInfo::envelope()
{
    return _envelope;
}

