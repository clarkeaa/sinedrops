#pragma once

class MTime;

class AREnvelope
{
public:
    AREnvelope();

    double calc(const MTime& gateOnTime,
                const MTime& currentTime) const;

    double calc(const MTime& gateOnTime,
                const MTime& gateOffTime,
                const MTime& currentTime) const;
    
    AREnvelope& setAttack(double attack);

    AREnvelope& setRelease(double release);
    
private:
    double _attack;
    double _release;
};
