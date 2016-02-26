#ifndef _TIMER_H_
#define _TIMER_H_

namespace sre
{

//! Class for Timer stuffs and FPS control.
class Timer
{
    private:
		unsigned int timeBegin;
		unsigned int timePaused;

		long elapsedTime;

		bool paused;
		bool started;

        static const unsigned int MILISECONDS_PER_FRAME = 1000 / 60;

    public:
		Timer();

		void start();
		void stop();
		void pause();
		void resume();

		unsigned int getTime();
		unsigned int getElapsedTime();

		bool isStarted();
		bool isPaused();

		void updateElapsedTime();

		void delay();
		void delay(unsigned int timeMS);
};

} // namespace
#endif
