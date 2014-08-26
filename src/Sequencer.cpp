#include "Sequencer.hpp"
#include "RandSequencer.hpp"
#include "MemLoopSequencer.hpp"
#include "CursesSequencer.hpp"

Sequencer* Sequencer::create()
{
    return CursesSequencer::create();
    //return RandSequencer::create();
    //return MemLoopSequencer::create();
}

