#pragma once

#include <string>

class Instrument;

class Sequencer
{
public:
    struct SequencerImpl;

    static Sequencer* create();

    virtual ~Sequencer();
    
    void update(const std::string& name, 
                Instrument* instrument,
                double currentTime);

private:
    Sequencer();

    SequencerImpl* _impl;
};
