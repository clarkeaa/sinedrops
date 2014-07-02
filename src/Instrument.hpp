#pragma once

class Voice;

class Instrument
{
public:
    static Instrument* create();
    Voice* nextVoice();
private:
};
