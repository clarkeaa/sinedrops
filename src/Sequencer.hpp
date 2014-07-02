#pragma once

#include <string>

class Instrument;

class Sequencer
{
public:
    static Sequencer* create();
    
    void update(const std::string& name, 
		Instrument* instrument,
		double currentTime);

private:
};
