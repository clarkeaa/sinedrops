#pragma once

#include "Voice.hpp"

class SineVoice : public Voice
{
public:
    struct SineVoiceImpl;
private:
    struct SineVoiceImpl* _impl;
};
