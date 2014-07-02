#include "Sequencer.hpp"

Sequencer* Sequencer::create()
{
    return new Sequencer();
}

void Sequencer::update(const std::string& name, 
		       Instrument* instrument,
		       double currentTime)
{
    
}
