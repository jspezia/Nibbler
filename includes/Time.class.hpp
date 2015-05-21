#ifndef TIME_CLASS_HPP
# define TIME_CLASS_HPP

# include <chrono>
# include <iostream>
# include <thread>

class Time
{
	public:
		~Time(void);

		/* returns unique instance of Time */
		static Time & Instance()
		{
			static Time		instance;

			return instance;
		}

		/* returns time since epoch in milliseconds */
		static int	 	GetTime();

		/* pause thread for an amount of milliseconds */
		static void 	Sleep(int milliseconds);

		/*
		** update time properties based on intern clock
		** - call this at the the start of game loop
		*/
		static void		Update();

		/* the time in seconds since the start of the game (Read Only) */
		static double	time;

		/* the time in seconds it took to complete the last frame (Read Only) */
		static double	deltaTime;

		/* the frame rate - frames per second (Read Only) */
		static double	fps;

		/* the total of frames since the start of the game (Read Only) */
		static int		frameCount;

	private:
		Time(void);
		Time(Time const & ref);
		Time & operator=(Time const & ref);

		/* the current time in milliseconds */
		static double	_currentTime;

		/* the time of last frame in milliseconds */
		static double	_lastTime;
};

#endif
