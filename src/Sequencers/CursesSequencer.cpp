
#include "CursesSequencer.hpp"
#include <curses.h>
#include "Instrument.hpp"
#include "Voice.hpp"

CursesSequencer::CursesSequencer()
    : _key(0),
      _noteCount(1)
{

}

void CursesSequencer::run()
{
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();/* Line buffering disabled. pass on everything */
    
    mvprintw(0, 0, "keyboard active (enter to exit):");
    refresh();
    int shouldLoop = 1;
    int count = 1;
    int middlec = 52;
    while(shouldLoop)
    {        
        c = getch();
        int key = 0;
        switch(c) {
        case ' ' : key = 1; break;
        case 'q': key = middlec; break;  //c
        case '2': key = middlec+1; break;//c#
        case 'w': key = middlec+2; break;//d
        case '3': key = middlec+3; break;//d#
        case 'e': key = middlec+4; break;//e
        case 'r': key = middlec+5; break;//f
        case '5': key = middlec+6; break;//f#
        case 't': key = middlec+7; break;//g
        case '6': key = middlec+8; break;//g#
        case 'y': key = middlec+9; break;//a
        case '7': key = middlec+10; break;//a#
        case 'u': key = middlec+11; break;//b
        case 'i': key = middlec+12; break;//c+1
        case 'z': key = middlec-12; break;  //c
        case 's': key = middlec-12+1; break;//c#
        case 'x': key = middlec-12+2; break;//d
        case 'd': key = middlec-12+3; break;//d#
        case 'c': key = middlec-12+4; break;//e
        case 'v': key = middlec-12+5; break;//f
        case 'g': key = middlec-12+6; break;//f#
        case 'b': key = middlec-12+7; break;//g
        case 'h': key = middlec-12+8; break;//g#
        case 'n': key = middlec-12+9; break;//a
        case 'j': key = middlec-12+10; break;//a#
        case 'm': key = middlec-12+11; break;//b
        case ',': key = middlec-12+12; break;//c+1
        case 10:
            shouldLoop = 0;
            break;
        default:
            break;
        }
        if (key>0) {
            mvprintw(count, 0, "keyDown: '%d'", key);
            count = (count + 1) % 40;
            _nextKey = key;
        } else {
            mvprintw(count, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c); 
            count = (count + 1) % 40;
        }
        refresh();
    }
    clrtoeol();
    refresh();
    endwin();
}

void CursesSequencer::update(const std::string& name, 
                             Instrument* instrument,
                             const MTime& currentTime)
{
    if (_nextKey > 0 && _nextKey != _key) {
        Voice* lastVoice = instrument->getVoice(_noteCount++);
    
        if (lastVoice) {
            lastVoice->gateOff(currentTime);
        }

        if (_nextKey > 1) {
            Voice* nextVoice = instrument->nextVoice(_noteCount);
            nextVoice->gateOn(currentTime, _nextKey, 60);
        }
        _key = _nextKey;
        _nextKey = 0;
    }
}

CursesSequencer* CursesSequencer::create()
{
    return new CursesSequencer();
}
