cmake_minimum_required(VERSION 2.8)
project(sinedrops)

include_directories(/opt/local/include)
find_library(PORTAUDIO portaudio)

add_executable(sinedrops 
    src/main.cpp 
    src/SineDrops.cpp) 
target_link_libraries(sinedrops ${PORTAUDIO})