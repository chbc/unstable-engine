#include "Timer.h"
#include <engine/systems/wrappers/multimedia/AMultimediaWrapper.h>

namespace sre
{

Timer::Timer()
{
	this->multimediaWrapper = AMultimediaWrapper::getInstance();

    this->timeBegin = 0;
	this->timePaused = 0;
	this->elapsedTime = 0;
	this->paused = false;
	this->started = false;
}

void Timer::start()
{
    this->started = true;
    this->paused = false;

	this->timeBegin = this->multimediaWrapper->getTicks();
}

void Timer::stop()
{
    this->started = false;
    this->paused = false;
}

void Timer::pause()
{
    if( ( this->started == true ) && ( this->paused == false ) )
    {
        this->paused = true;
		this->timePaused = this->multimediaWrapper->getTicks() - this->timeBegin;
    }
}

void Timer::resume()
{
	if( this->paused == true )
    {
        this->paused = false;
		this->timeBegin = this->multimediaWrapper->getTicks() - this->timePaused;
        this->timePaused = 0;
    }
}

unsigned int Timer::getTime()
{
    if( this->started == true )
    {
        if( this->paused == true )
        {
			return this->timePaused;
        }
        else
        {
			return this->multimediaWrapper->getTicks() - this->timeBegin;
        }
    }

    return 0;
}

unsigned int Timer::getElapsedTime()
{
    return this->elapsedTime;
}

bool Timer::isStarted()
{
	return this->started;
}

bool Timer::isPaused()
{
    return this->paused;
}

void Timer::updateElapsedTime()
{
    this->elapsedTime = this->multimediaWrapper->getTicks() - this->timeBegin;
}

void Timer::delay()
{
	unsigned int time = this->getTime();
	if( time < MILISECONDS_PER_FRAME )
		this->multimediaWrapper->delay( MILISECONDS_PER_FRAME - time );
}

} // namespace
