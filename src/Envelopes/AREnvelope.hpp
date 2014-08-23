#pragma once

#include "Envelope.hpp"

class AREnvelope : public Envelope
{
public:
    AREnvelope();

    virtual double calc(const MTime& gateOnTime,
                        const MTime& currentTime) const override;
    
    virtual double calc(const MTime& gateOnTime,
                        const MTime& gateOffTime,
                        const MTime& currentTime) const override;
    
    AREnvelope& setAttack(double attack);

    AREnvelope& setRelease(double release);
    
private:
    double _attack;
    double _release;
};
