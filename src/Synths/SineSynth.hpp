
#pragma once

#include "Synth.hpp"

class Envelope;

class SineSynth : public Synth
{
public:
    typedef std::function<double(int)> ScaleFunc;

    SineSynth();
    
    virtual ~SineSynth();
    
    void setEnvelope(Envelope* envelope);
    
    Envelope* envelope();

    void setScale(const ScaleFunc& scaleFunc);

    virtual const ScaleFunc& scale() const override;

    virtual int fillBuffer(float* buffer,
                           unsigned long frameCount, 
                           const MTime& currentTime,
                           double freq,
                           double amp,
                           const GateInfo& gateOnInfo,
                           const GateInfo& gateOffInfo) override;
        
private:
    Envelope* _envelope;
    ScaleFunc _scale;
};
