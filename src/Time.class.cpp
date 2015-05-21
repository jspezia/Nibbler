#include <Time.class.hpp>

Time::Time(void) {}
Time::~Time(void) {}

int Time::GetTime()
{
	auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
	// std::cout << "Time since epoch: " << std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch).count() /* / (60 * 60 * 24 * 365) */<< std::endl;
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch).count();
	return ms;
}

void Time::Sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Time::Update()
{
	/* get current time in milliseconds */
	currentTime = GetTime();

	/* calculate elapsed time since last frame */
	if (lastTime)
		deltaTime = currentTime - lastTime;

	/* set lastTime for next frame */
	lastTime = currentTime;

	/* add elapsed time to game time */
	time += deltaTime;

	/* calculate fps */
	fps = 1.0f / deltaTime * 1000;

	/* increment frame count */
	frameCount += 1;
}

double	Time::time = 0;
double	Time::currentTime = 0;
double	Time::lastTime = 0;
double	Time::deltaTime = 0;
double	Time::fps = 0;
int		Time::frameCount = 0;
