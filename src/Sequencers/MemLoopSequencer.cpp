#include "MemLoopSequencer.hpp"
#include <stdint.h>
#include "Voice.hpp"
#include "Instrument.hpp"
#include <cstdlib>
#include <iostream>
#include "MTime.hpp"
#include <cstring>

#define NO_NOTE {000,000}
#define OFF_NOTE {-1, -1}
static const int s_seqWidth = 10;
static const int s_seqLength = 64;
static int s_seq[s_seqLength][s_seqWidth][2] = {
    /*00*/ {{060, 35},   NO_NOTE,  NO_NOTE, {060, 30},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*01*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*02*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*03*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*04*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE, {060, 33},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*05*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*06*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*07*/ { OFF_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*08*/ {{060, 40},   NO_NOTE,  NO_NOTE, {060, 39},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*09*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*10*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*11*/ {  NO_NOTE, {060, 50},  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*12*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE, {060, 43},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*13*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*14*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*15*/ { OFF_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*16*/ {{060, 32},   NO_NOTE,  NO_NOTE, {060, 46},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*17*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*18*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*19*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*20*/ {  NO_NOTE,  OFF_NOTE,  NO_NOTE, {060, 43},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*21*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*22*/ {  NO_NOTE, {060, 52},  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*23*/ { OFF_NOTE,  OFF_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*24*/ {{060, 37}, {060, 48},  NO_NOTE, {060, 40},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*25*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*26*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*27*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*28*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE, {060, 39},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*29*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*30*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*31*/ { OFF_NOTE,  OFF_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*32*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*33*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*34*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE, {060, 33},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*35*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*36*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*37*/ { OFF_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*38*/ {{060, 40},   NO_NOTE,  NO_NOTE, {060, 39},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*39*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*40*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*41*/ {  NO_NOTE, {060, 50},  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*42*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE, {060, 43},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*43*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*44*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*45*/ { OFF_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*46*/ {{060, 32},   NO_NOTE,  NO_NOTE, {060, 48},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*47*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*48*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*49*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*50*/ {  NO_NOTE,  OFF_NOTE,  NO_NOTE, {060, 43},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*51*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*52*/ {  NO_NOTE, {060, 54},  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*53*/ { OFF_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*54*/ {{060, 37},   NO_NOTE,  NO_NOTE, {060, 45},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*55*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*56*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*57*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*58*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE, {060, 39},  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*59*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*60*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*61*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*62*/ {  NO_NOTE,   NO_NOTE,  NO_NOTE,   NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
    /*63*/ { OFF_NOTE,  OFF_NOTE,  NO_NOTE,  OFF_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE,  NO_NOTE},
};
static double s_bpm = 120.0;


struct MemLoopSequencer::MemLoopSequencerImpl {
    uint64_t count;
    uint32_t noteCount;
    uint32_t activeNotes[s_seqWidth];

    MemLoopSequencerImpl()
        : count(0), noteCount(1)
        {
            memset(activeNotes, 0, sizeof(activeNotes));
        }
};

MemLoopSequencer* MemLoopSequencer::create()
{
    return new MemLoopSequencer();
}

MemLoopSequencer::MemLoopSequencer()
    : _impl(new MemLoopSequencerImpl())
{
}

MemLoopSequencer::~MemLoopSequencer()
{
    delete _impl;
}

void MemLoopSequencer::update(const std::string& name, 
                              Instrument* instrument,
                              const MTime& currentTime)
{
    int ticksPerBeat = 8;
    double minutesPerSecond = 1.0/60.0;
    double ticksPerSecond = s_bpm * ticksPerBeat * minutesPerSecond;
    uint64_t div = currentTime.seconds() * ticksPerSecond;
    if (div > _impl->count) {
        _impl->count = div;
        int loc = div % s_seqLength;
        printf("%05lld %02d | ", div, loc);
        for (int i=0; i < s_seqWidth; ++i) {
            int note[2] = {s_seq[loc][i][0], s_seq[loc][i][1]};
            printf("%03d %02d | ", note[0], note[1]);
            if (note[0] > 0) {
                Voice* voice = instrument->nextVoice(_impl->noteCount);
                _impl->activeNotes[i] = _impl->noteCount;
                _impl->noteCount += 1;
                voice->gateOn(currentTime, note[1], note[0]);
            } else if (note[0] < 0) {
                uint32_t note = _impl->activeNotes[i];
                Voice* voice = instrument->getVoice(note);
                if (voice) {
                    voice->gateOff(currentTime);
                    _impl->activeNotes[i] = 0;
                }
            }
        }
        printf("\n");
    }
}

void MemLoopSequencer::run()
{
    std::cout << "press enter key..." << std::endl;
    int inchar = getchar();
    (void)inchar;   
}
