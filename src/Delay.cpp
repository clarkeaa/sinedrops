
#include "Delay.hpp"

#include "MTime.hpp"
#include "RingBuffer.hpp"
#include <cstdlib>
#include "MixTool.hpp"

static const int s_numChannels = 2;

struct Delay::DelayImpl {
    MTime duration;
    float wetDry;
    float feedBack;
    RingBuffer<float>* buffer;

    DelayImpl(const MTime& argDuration,
              float argWetDry,
              float argFeedBack)
        : duration(argDuration),
          wetDry(argWetDry),
          feedBack(argFeedBack),
          buffer(new RingBuffer<float>(24000*2)) {}

    ~DelayImpl() {
        if (buffer) {
            delete buffer;
        }
    }
};


Delay::Delay(const MTime& duration,
             float wetDry,
             float feedBack)
    : _impl(new DelayImpl(duration, wetDry, feedBack))
{
    
}

Delay::~Delay()
{
    delete _impl;
}

int Delay::fillBuffer(float* buffer, 
                      unsigned long frameCount, 
                      const MTime& currentTime)
{
    uint32_t bufferLen = frameCount * s_numChannels;
    uint32_t chunkSize = 
        (bufferLen > _impl->buffer->size())?
        _impl->buffer->size():
        bufferLen;
    float chunk[chunkSize];
    uint32_t numWroteToBuffer = 0;
    while(numWroteToBuffer < bufferLen) {
        if (numWroteToBuffer + chunkSize >= bufferLen) {
            chunkSize = bufferLen - numWroteToBuffer;
        }

        _impl->buffer->read(chunkSize, chunk);
        for(uint32_t i=0; i < chunkSize; ++i) {
            chunk[i] *= 0.5;
        }
        MixTool::mix(buffer, chunk, chunkSize);
        _impl->buffer->write(chunkSize, buffer);

        numWroteToBuffer+=chunkSize;
        buffer += chunkSize;
    }

    return 0;
}
