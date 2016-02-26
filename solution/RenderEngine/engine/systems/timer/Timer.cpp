#include "Timer.h"
#include <SDL/SDL.h>

namespace sre
{

Timer::Timer()
{
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

	this->timeBegin = SDL_GetTicks();
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
		this->timePaused = SDL_GetTicks() - this->timeBegin;
    }
}

void Timer::resume()
{
	if( this->paused == true )
    {
        this->paused = false;
		this->timeBegin = SDL_GetTicks() - this->timePaused;
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
			return SDL_GetTicks() - this->timeBegin;
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
    this->elapsedTime = SDL_GetTicks() - this->timeBegin;
}

void Timer::delay()
{
	unsigned int time = this->getTime();
	if( time < MILISECONDS_PER_FRAME )
		SDL_Delay( MILISECONDS_PER_FRAME - time );
}

void Timer::delay(unsigned int timeMS)
{
	SDL_Delay(timeMS);
}

} // namespace
