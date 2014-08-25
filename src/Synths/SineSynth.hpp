
#pragma once

#include "Synth.hpp"

class Envelope;

class SineSynth : public Synth
{
public:
    SineSynth();
    
    virtual ~SineSynth();
    
    void setEnvelope(Envelope* envelope);
    
    Envelope* envelope();

    void setScale(const ScaleFunc& scaleFunc);

    virtual const ScaleFunc& scale() const override;

    virtual int fillBuffer(const RenderInfo& rinfo,
                           double freq,
                           double amp,
                           const GateInfo& gateOnInfo,
                           const GateInfo& gateOffInfo) override;
        
private:
    Envelope* _envelope;
    ScaleFunc _scale;
};
