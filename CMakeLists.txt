cmake_minimum_required(VERSION 2.8)
project(sinedrops)

find_library(PORTAUDIO portaudio)

include_directories(./src)
include_directories(./src/Effects)
include_directories(./src/Envelopes)
include_directories(./src/Sequencers)
include_directories(./src/Synths)
include_directories(/opt/local/include)

add_executable(sinedrops 
    src/Effects/Delay.cpp
    src/Envelope.cpp
    src/Envelopes/AREnvelope.cpp
    src/Instrument.cpp
    src/MTime.cpp
    src/MixTool.cpp
    src/Object.cpp
    src/RenderOptions.cpp
    src/Sequencer.cpp
    src/Sequencers/MemLoopSequencer.cpp
    src/Sequencers/RandSequencer.cpp
    src/SineDrops.cpp
    src/Synths/SineSynth.cpp
    src/Voice.cpp
    src/main.cpp 
    ) 
target_link_libraries(sinedrops ${PORTAUDIO})
