#include "AREnvelope.hpp"
#include "MTime.hpp"
#include <algorithm>

AREnvelope::AREnvelope()
    : _attack(0),
      _release(0)
{

}

double AREnvelope::calc(const MTime& gateOnTime,
                        const MTime& currentTime) const
{
    MTime mtimeIn = currentTime - gateOnTime;
    double timeIn = mtimeIn.seconds();
    return std::min((1.0/_attack)*timeIn, 1.0);
}

double AREnvelope::calc(const MTime& gateOnTime,
                        const MTime& gateOffTime,
                        const MTime& currentTime) const
{
    MTime mtimeSince = currentTime - gateOffTime;
    double timeSince = mtimeSince.seconds();
    return std::max(1.0 + (-1.0/_release) * timeSince, 0.0);
}

AREnvelope& AREnvelope::setAttack(double attack)
{
    _attack = attack;
    return *this;
}

AREnvelope& AREnvelope::setRelease(double release)
{
    _release = release;
    return *this;
}
