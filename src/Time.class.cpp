#include <Time.class.hpp>

Time::Time(void) {}
Time::~Time(void) {}

int Time::GetTime()
{
	auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
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
	_currentTime = GetTime();

	/* calculate elapsed time in seconds since last frame */
	if (_lastTime)
		deltaTime = (_currentTime - _lastTime) / 1000.f;

	/* set lastTime for next frame */
	_lastTime = _currentTime;

	/* add elapsed time to game time */
	time += deltaTime;

	/* calculate fps */
	fps = 1.0f / deltaTime;

	/* increment frame count */
	frameCount += 1;
}

/* initialize static properties */
double	Time::time = 0;
double	Time::deltaTime = 0;
double	Time::fps = 0;
int		Time::frameCount = 0;

double	Time::_currentTime = 0;
double	Time::_lastTime = 0;
