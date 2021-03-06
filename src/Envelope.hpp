#pragma once

class MTime;
class GateInfo;

#include "Object.hpp"

class Envelope : public Object
{
public:
    virtual ~Envelope() {}

    virtual double calc(const MTime& gateOnTime,
                        const MTime& currentTime) const =0;

    virtual double calc(const MTime& gateOnTime,
                        const MTime& gateOffTime,
                        const MTime& currentTime) const =0;

    static double calc(const Envelope* env,
                       const GateInfo& gateOnTime,
                       const GateInfo& gateOffTime,
                       const MTime& currentTime);
};
