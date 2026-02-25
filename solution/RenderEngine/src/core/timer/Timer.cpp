#include "Timer.h"
#include "AMultimediaWrapper.h"

namespace sre
{

Timer::Timer(AMultimediaWrapper *multimediaWrapper) 
    : timeBegin(0), frameProcessingTime(0), lastFrameTime(0)
{
    this->multimediaWrapper = multimediaWrapper;
}

void Timer::start()
{
    this->timeBegin = this->multimediaWrapper->getTicks();
}

uint32_t Timer::stop()
{
    this->frameProcessingTime = this->multimediaWrapper->getTicks() - this->timeBegin;
    return this->frameProcessingTime;
}

uint32_t Timer::getframeProcessingTime()
{
    return this->frameProcessingTime;
}

uint32_t Timer::getLastFrameTime()
{
    return this->lastFrameTime;
}

void Timer::delay()
{
    if (this->frameProcessingTime < MILISECONDS_PER_FRAME)
        this->multimediaWrapper->delay(MILISECONDS_PER_FRAME - this->frameProcessingTime);

    this->lastFrameTime = this->multimediaWrapper->getTicks() - this->timeBegin;
}

} // namespace
