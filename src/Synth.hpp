#pragma once

#include "Object.hpp"
#include <functional>

class MTime;
class GateInfo;
struct RenderInfo;

class Synth : public Object
{
public:
    typedef std::function<double(int)> ScaleFunc;

    virtual ~Synth() {}

    virtual const ScaleFunc& scale() const =0;
    
    virtual int fillBuffer(const RenderInfo& rinfo,
                           double freq,
                           double amp,
                           const GateInfo& gateOnInfo,
                           const GateInfo& gateOffInfo) =0;
};
