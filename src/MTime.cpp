#include "MTime.hpp"
#include <cassert>

double MTime::seconds() const
{
    return static_cast<double>(value) / 
        static_cast<double>(timescale);
}

MTime MTime::operator-(const MTime& operand) const
{
    assert(this->timescale == operand.timescale);
    return (MTime) {
        .value = this->value - operand.value,
        .timescale = this->timescale
    };
}
