#pragma once

#include "Sequencer.hpp"
#include <stdint.h>

class CursesSequencer : public Sequencer
{
public:
    static CursesSequencer* create();

    CursesSequencer();
    
    virtual void run() override;

    virtual void update(const std::string& name, 
                        Instrument* instrument,
                        const MTime& currentTime) override;
private:
    int _key;
    int _nextKey;
    uint32_t _noteCount;
};
