#include "Timer.h"
#include <engine/core/wrappers/multimedia/AMultimediaWrapper.h>

namespace sre
{

Timer::Timer(AMultimediaWrapper *multimediaWrapper) 
    : timeBegin(0), elapsedTime(0), lastFrameTime(0)
{
    this->multimediaWrapper = multimediaWrapper;
}

void Timer::start()
{
    this->timeBegin = this->multimediaWrapper->getTicks();
}

uint32_t Timer::stop()
{
    this->elapsedTime = this->multimediaWrapper->getTicks() - this->timeBegin;
    return this->elapsedTime;
}

uint32_t Timer::getElapsedTime()
{
    return this->elapsedTime;
}

uint32_t Timer::getLastFrameTime()
{
    return this->lastFrameTime;
}

void Timer::delay()
{
    if (elapsedTime < MILISECONDS_PER_FRAME)
        this->multimediaWrapper->delay(MILISECONDS_PER_FRAME - elapsedTime);

    this->lastFrameTime = this->multimediaWrapper->getTicks() - this->timeBegin;
}

} // namespace
