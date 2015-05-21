#ifndef TIME_CLASS_HPP
# define TIME_CLASS_HPP

# include <chrono>
# include <iostream>
# include <thread>

class Time
{
	public:
		~Time(void);

		static Time & Instance()
		{
			static Time		instance;

			return instance;
		}

		static int	 	GetTime();
		static void 	Sleep(int milliseconds);
		static void		Update();

		static double	time;
		static double	currentTime;
		static double	lastTime;
		static double	deltaTime;

		static double	fps;
		static int		frameCount;

	private:
		Time(void);
		Time(Time const & ref);
		Time & operator=(Time const & ref);
};

#endif
