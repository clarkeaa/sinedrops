#pragma once

#include <string>

class Instrument;
class MTime;

class Sequencer
{
public:
    struct SequencerImpl;

    static Sequencer* create();

    virtual ~Sequencer();
    
    void update(const std::string& name, 
                Instrument* instrument,
                const MTime& currentTime);

private:
    Sequencer();

    SequencerImpl* _impl;
};
