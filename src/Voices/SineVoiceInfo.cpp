
#include "SineVoiceInfo.hpp"
#include <cmath>

static double chromatic(int key)
{
    return pow(2.0, (key + 48) / 12.0);
}

SineVoiceInfo::SineVoiceInfo()
    : scale(chromatic)
{
    
}

