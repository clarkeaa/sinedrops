#pragma once

class Voice;

class VoiceFactory
{
public:
    virtual Voice* makeVoice() = 0;
};
