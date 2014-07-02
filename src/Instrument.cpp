#include "Instrument.hpp"
#include <cstdlib>

Instrument* Instrument::create()
{
    return new Instrument();
}

Voice* Instrument::nextVoice()
{
    return NULL;
}
