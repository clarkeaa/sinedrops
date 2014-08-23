#include "Sequencer.hpp"
#include "RandSequencer.hpp"
#include "MemLoopSequencer.hpp"

Sequencer* Sequencer::create()
{
    return RandSequencer::create();
    //return MemLoopSequencer::create();
}

