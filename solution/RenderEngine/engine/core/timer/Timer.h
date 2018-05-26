#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

namespace sre
{

class AMultimediaWrapper;

//! Class for Timer stuffs and FPS control.
class Timer
{
    private:
        AMultimediaWrapper *multimediaWrapper;
        uint32_t timeBegin;
        uint32_t elapsedTime;
        uint32_t lastFrameTime;

        static const uint32_t MILISECONDS_PER_FRAME = 1000 / 60;

    private:
        Timer(AMultimediaWrapper *multimediaWrapper);

        void start();
        uint32_t stop();
        uint32_t getElapsedTime();
        void delay();
        uint32_t getLastFrameTime();

friend class MultimediaManager;
};

} // namespace
#endif
