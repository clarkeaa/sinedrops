#pragma once

#include <string>

class Instrument;
class MTime;

class Sequencer
{
public:
    static Sequencer* create();

    virtual ~Sequencer() {}
    
    virtual void update(const std::string& name, 
                        Instrument* instrument,
                        const MTime& currentTime) =0;
};
