#include "Game.class.hpp"
#include "Player.class.hpp"
#include "Map.class.hpp"
#include "Time.class.hpp"
#include "DynamicLibHandler.class.hpp"
#include "KeyValue.hpp"
#include "Lib.hpp"
#include "Snake.class.hpp"

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

	// gen player position
	int x = width / 2;
	int y = height / 2;

	this->_player = new Player(x, y);
	this->init();
}


Game::~Game(void)
{
	// delete all
	delete this->_player;
	delete this->_map;
}

/* GETTERS */
Map *		Game::getMap(void) const
{
	return this->_map;
}

Player *	Game::getPlayer(void) const
{
	return this->_player;
}

/* SETTERS */

/* CORE */
void		Game::init(void)
{
	//tmp
	std::string				path = "./libnibbler_sfml.so";
	DynamicLibHandler::instance().setHandle(path, this->_width, this->_height);
	this->_dlib = DynamicLibHandler::instance().getLib();
	//
}

void		Game::loop(void)
{
	//test class Snake
	Snake		snake(3, 3);

	while (!this->_shouldExit)
	{
		Time::update();

		// do stuff..
		this->_dlib->draw(&snake);

		int keycode = 0;
		if ((keycode = this->_dlib->getInput()) != 0)
		{
			if (keycode == KeyEscape)
				this->_shouldExit = TRUE;
		}
		if (keycode == KeyUp)
			snake.move(NORTH);
		else if (keycode == KeyDown)
			snake.move(SOUTH);
		else if (keycode == KeyLeft)
			snake.move(WEST);
		else if (keycode == KeyRight)
			snake.move(EAST);
		else
			snake.move(snake.getDirection());
		// std::cout << "Fps = " << Time::fps << std::endl;

		Time::sleep(100);
	}
}
