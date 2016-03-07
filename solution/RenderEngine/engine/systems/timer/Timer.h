#ifndef _TIMER_H_
#define _TIMER_H_

namespace sre
{

class AMultimediaWrapper;

//! Class for Timer stuffs and FPS control.
class Timer
{
    private:
		AMultimediaWrapper *multimediaWrapper;

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
};

} // namespace
#endif
