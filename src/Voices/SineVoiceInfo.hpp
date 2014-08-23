
#pragma once

#include "Object.hpp"
#include <functional>

class Envelope;

class SineVoiceInfo : public Object
{
public:
    SineVoiceInfo();
    
    virtual ~SineVoiceInfo();

    std::function<double(int)> scale;
    
    void setEnvelope(Envelope* envelope);
    
    Envelope* envelope();

private:
    Envelope* _envelope;
};
