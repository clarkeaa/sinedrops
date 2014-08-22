#pragma once

#include "Sequencer.hpp"

class MemLoopSequencer : public Sequencer
{
public:
    struct MemLoopSequencerImpl;

    static MemLoopSequencer* create();

    virtual ~MemLoopSequencer();
    
    void update(const std::string& name, 
                Instrument* instrument,
                const MTime& currentTime);

private:
    MemLoopSequencer();

    MemLoopSequencerImpl* _impl;
};
