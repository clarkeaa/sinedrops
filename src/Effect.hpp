
#pragma once

class MTime;
struct RenderInfo;

class Effect
{
public:
    virtual ~Effect() {}

    virtual int fillBuffer(const RenderInfo& rinfo) =0;
};
