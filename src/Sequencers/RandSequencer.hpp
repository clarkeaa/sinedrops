#pragma once

#include "Sequencer.hpp"

class RandSequencer : public Sequencer
{
public:
    struct RandSequencerImpl;

    static RandSequencer* create();

    virtual ~RandSequencer();

    
    virtual void run() override; 

    virtual void update(const std::string& name, 
                        Instrument* instrument,
                        const MTime& currentTime) override;

private:
    RandSequencer();

    RandSequencerImpl* _impl;
};
