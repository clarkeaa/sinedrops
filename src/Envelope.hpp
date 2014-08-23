#pragma once

class MTime;

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
};
