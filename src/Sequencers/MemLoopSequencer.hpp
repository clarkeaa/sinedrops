#pragma once

#include "Sequencer.hpp"

class MemLoopSequencer : public Sequencer
{
public:
    struct MemLoopSequencerImpl;

    static MemLoopSequencer* create();

    virtual ~MemLoopSequencer();
    
    virtual void run() override; 

    virtual void update(const std::string& name, 
                        Instrument* instrument,
                        const MTime& currentTime) override;

private:
    MemLoopSequencer();

    MemLoopSequencerImpl* _impl;
};
