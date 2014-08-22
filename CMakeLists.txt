cmake_minimum_required(VERSION 2.8)
project(sinedrops)

include_directories(/opt/local/include)
find_library(PORTAUDIO portaudio)

add_executable(sinedrops 
    src/AREnvelope.cpp
    src/Instrument.cpp
    src/MTime.cpp
    src/Sequencer.cpp
    src/SineDrops.cpp
    src/SineVoice.cpp
    src/RandSequencer.cpp
    src/main.cpp 
    ) 
target_link_libraries(sinedrops ${PORTAUDIO})
