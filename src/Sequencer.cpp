#include "Sequencer.hpp"
#include "RandSequencer.hpp"

Sequencer* Sequencer::create()
{
    return RandSequencer::create();
}

