#include "Game.class.hpp"
#include "Map.class.hpp"
#include "Time.class.hpp"

/*
	initiatialize game
		|
		|__ load resources
				|
				|__ game loop
			--->(
			|		process inputs
			|		simulate game world
			|			(run AI)
			|			(move)
			|			(collitions detection)
			|			(update score | lives | ...)
			|		render
			|		check shutdown conditions
			|___)		|
						|__ unload resources
								|
								|__ exit
*/

Game::Game(int const width, int const height) : _width(width), _height(height), _shouldExit(false)
{
	this->_map = new Map(width, height);
}


Game::~Game(void)
{
	return;
}

void	Game::loop(void)
{
	while (!this->_shouldExit)
	{
		Time::update();
		// do stuff..

		std::cout << "Time: " << Time::time << " sec" << std::endl;

		Time::sleep(100);
	}
}
