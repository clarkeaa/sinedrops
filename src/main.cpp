#include <portaudio.h>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <assert.h>
#include <stdint.h>
#include "SineDrops.hpp"
#include "MTime.hpp"
#include <memory>
#include "RenderOptions.hpp"
#include "RenderInfo.hpp"

typedef float  float32_t;
typedef double float64_t;

static const PaSampleFormat s_sampleFormat = paFloat32;
static const size_t s_sampleSize = sizeof(float32_t);

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
        .timescale = static_cast<uint32_t>(kSampleRate)
    };
    SineDrops* sineDrops = callbackState->sineDrops;
    RenderInfo rinfo = {
        .buffer = buffer,
        .frameCount = frameCount,
        .currentTime = time,
    };
    int answer = sineDrops->fillBuffer(rinfo);

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
        .channelCount = kNumChannels,
        .sampleFormat = s_sampleFormat,
        .suggestedLatency = 0.1,
        .hostApiSpecificStreamInfo = NULL,
    };
    unsigned long framesPerBuffer = 1024;//paFramesPerBufferUnspecified;
    PaStreamFlags streamFlags = 0;   
    
    std::shared_ptr<SineDrops> 
        sineDrops(SineDrops::create(kNumChannels, kSampleRate));

    CallbackState callbackState = {
        .time = 0,
        .sineDrops = sineDrops.get(),
    };

    PaError err = 
        Pa_OpenStream( &stream,
                       NULL,
                       &outputParameters,
                       kSampleRate,
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
