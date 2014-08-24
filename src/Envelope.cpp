
#include "Envelope.hpp"

#include "GateInfo.hpp"

double Envelope::calc(const Envelope* env,
                      const GateInfo& gateOnTime,
                      const GateInfo& gateOffTime,
                      const MTime& currentTime)
{
    if (gateOnTime.isSet) {
        if (gateOffTime.isSet) {
            return env->calc(gateOnTime.time,
                             gateOffTime.time,
                             currentTime);
        } else {
            return env->calc(gateOnTime.time,
                             currentTime);
        }
    } else {
        return 0.0;
    }
}
