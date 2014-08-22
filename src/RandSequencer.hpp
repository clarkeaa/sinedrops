#pragma once

#include "Sequencer.hpp"

class RandSequencer : public Sequencer
{
public:
    struct RandSequencerImpl;

    static RandSequencer* create();

    virtual ~RandSequencer();
    
    void update(const std::string& name, 
                Instrument* instrument,
                const MTime& currentTime);

private:
    RandSequencer();

    RandSequencerImpl* _impl;
};
