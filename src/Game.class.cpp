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

int			Game::collision(Map const *map)
{
	Snake		*snake;

	snake = map->getSnake();
	if (snake->_head->getX() < 0  || snake->_head->getX() > map->getWidth()
		|| snake->_head->getY() < 0 || snake->_head->getY() > map->getHeight())
	{
		return TRUE;
		printf("bang the wall.\n GAME OVER ! \n");
	}

	for (std::list<GameEntity *>::iterator it = snake->_body.begin(); it != snake->_body.end(); it++)
	{
		if ((*it)->getX() == snake->_head->getX() && (*it)->getY() == snake->_head->getY())
		{
			printf("the head in the ass\n GAME OVER ! \n");
			return TRUE;
		}
	}

	return FALSE;
}

void		Game::loop(void)
{
	//test class Snake
	Map			*map;

	map = this->getMap();

	Snake		snake(map->getHeight() / 2, map->getWidth() / 2);
	map->setSnake(&snake);
	while (!this->_shouldExit)
	{
		Time::update();

		// draw map
		this->_dlib->draw(map);

		this->_shouldExit = this->collision(map);

		// check input && update snake
		int keycode = 0;
		if ((keycode = this->_dlib->getInput()) != 0)
		{
			if (keycode == KeyEscape)
				this->_shouldExit = TRUE;
		}
		if (keycode == KeySpace)
			snake.setState("grow");
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
