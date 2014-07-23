#include "MTime.hpp"


double MTime::seconds() const
{
    return static_cast<double>(value) / 
        static_cast<double>(timescale);
}
