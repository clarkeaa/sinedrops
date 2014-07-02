#include <portaudio.h>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <assert.h>
#include <stdint.h>
typedef float  float32_t;
typedef double float64_t;

static const int s_channelCount = 2;
static const PaSampleFormat s_sampleFormat = paFloat32;
static const size_t s_sampleSize = sizeof(float32_t);

static int callback(const void *input, 
		    void *output, 
		    unsigned long frameCount, 
		    const PaStreamCallbackTimeInfo *timeInfo, 
		    PaStreamCallbackFlags statusFlags, 
		    void *userData)
{
    memset(output, 0, s_sampleSize * s_channelCount * frameCount);
    return 0;
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
    double sampleRate = 44100;
    unsigned long framesPerBuffer = 512;
    PaStreamFlags streamFlags = 0;   
    
    PaError err = 
	Pa_OpenStream( &stream,
		       NULL,
		       &outputParameters,
		       sampleRate,
		       framesPerBuffer,
		       streamFlags,
		       callback,
		       NULL) ;
    assert(err == paNoError);

    Pa_StartStream(stream);
    
    std::cout << "press enter key..." << std::endl;
    int inchar = getchar();

    Pa_StopStream(stream);

    Pa_Terminate();
    
    return 0;
}