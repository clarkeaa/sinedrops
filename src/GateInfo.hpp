#pragma once

#include "MTime.hpp"

struct GateInfo {
    MTime time;
    bool isSet;
    GateInfo() : time(), isSet(false) {}
    GateInfo(const MTime& argTime) 
        : time(argTime), isSet(true) {}
};
