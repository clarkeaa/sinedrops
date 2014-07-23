#pragma once

#include <stdint.h>

struct MTime {
    uint64_t value;
    uint32_t timescale;

    double seconds() const;
};
