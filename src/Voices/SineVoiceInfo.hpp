
#pragma once

#include "Object.hpp"
#include <functional>

class SineVoiceInfo : public Object
{
public:
    SineVoiceInfo();
    
    std::function<double(int)> scale;    
};
