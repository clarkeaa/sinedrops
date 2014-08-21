#include <portaudio.h>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <assert.h>
#include <stdint.h>
#include "SineDrops.hpp"
#include "MTime.hpp"
#include <memory>

typedef float  float32_t;
typedef double float64_t;

static const int s_channelCount = 2;
static const PaSampleFormat s_sampleFormat = paFloat32;
static const size_t s_sampleSize = sizeof(float32_t);
static const double s_sampleRate = 44100;

namespace {
    struct CallbackState {
        uint64_t time;
        SineDrops* sineDrops;
    };
}

static int callback(const void *input, 
                    void *output, 
                    unsigned long frameCount, 
                    const PaStreamCallbackTimeInfo *timeInfo, 
                    PaStreamCallbackFlags statusFlags, 
                    void *userData)
{
    float* buffer = static_cast<float*>(output);
    CallbackState* callbackState = 
        static_cast<CallbackState*>(userData);
    MTime time = {
        .value = callbackState->time,
        .timescale = static_cast<uint32_t>(s_sampleRate)
    };
    SineDrops* sineDrops = callbackState->sineDrops;
    int answer = sineDrops->fillBuffer(buffer, 
                                       frameCount, 
                                       time);

    callbackState->time += frameCount;

    return answer;
}

int main(int argc, const char* argv[])
{
    Pa_Initialize();
    PaStream* stream;
    PaDeviceIndex outputDevice = Pa_GetDefaultOutputDevice();
    PaStreamParameters outputParameters = {
        .device = outputDevice,
        .channelCount = s_channelCount,
        .sampleFormat = s_sampleFormat,
        .suggestedLatency = 0.1,
        .hostApiSpecificStreamInfo = NULL,
    };
    unsigned long framesPerBuffer = paFramesPerBufferUnspecified;
    PaStreamFlags streamFlags = 0;   
    
    std::shared_ptr<SineDrops> 
        sineDrops(SineDrops::create(s_channelCount, s_sampleRate));

    CallbackState callbackState = {
        .time = 0,
        .sineDrops = sineDrops.get(),
    };

    PaError err = 
        Pa_OpenStream( &stream,
                       NULL,
                       &outputParameters,
                       s_sampleRate,
                       framesPerBuffer,
                       streamFlags,
                       callback,
                       &callbackState) ;
    assert(err == paNoError);

    Pa_StartStream(stream);
    
    std::cout << "press enter key..." << std::endl;
    int inchar = getchar();

    Pa_StopStream(stream);

    Pa_Terminate();
    
    return 0;
}
