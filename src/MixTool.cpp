
#include "MixTool.hpp"

namespace MixTool {

    void mix(float* dst, float* src, unsigned long count)
    {
        unsigned long n = (count + 7) / 8;
        switch(count % 8) {
        case 0:do {*dst++ += *src++;
            case 7:*dst++ += *src++;
            case 6:*dst++ += *src++;
            case 5:*dst++ += *src++;
            case 4:*dst++ += *src++;
            case 3:*dst++ += *src++;
            case 2:*dst++ += *src++;
            case 1:*dst++ += *src++;
            } while(--n > 0);
        }
    }

}
