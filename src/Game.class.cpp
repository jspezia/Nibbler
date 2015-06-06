#include "Game.class.hpp"
#include "Player.class.hpp"
#include "Map.class.hpp"
#include "Time.class.hpp"
#include "DynamicLibHandler.class.hpp"
#include "KeyValue.hpp"
#include "Lib.hpp"
#include "Snake.class.hpp"
#include "GameEntity.class.hpp"
#include <cstdlib>

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

	this->init();
}


Game::~Game(void)
{
	// delete all
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

/* CORE */
void		Game::init(void)
{
	//tmp
	std::string				path = "./libnibbler_ncurses.so";
	DynamicLibHandler::instance().setHandle(path, this->_width, this->_height);
	this->_dlib = DynamicLibHandler::instance().getLib();
}

int			Game::collision(void)
{
	Snake		*snake;
	Map			*map;

	map = getMap();
	snake = map->getSnake();

	// with the edge
	if (snake->_head->getX() < 0  || snake->_head->getX() > map->getWidth() - 1
		|| snake->_head->getY() < 0 || snake->_head->getY() > map->getHeight() - 1) {
		printf("bang the wall.\n GAME OVER ! \n");
		return TRUE;
	}

	// with himself
	for (std::list<GameEntity *>::iterator it = snake->_body.begin(); it != snake->_body.end(); it++) {
		if ((*it)->getX() == snake->_head->getX() && (*it)->getY() == snake->_head->getY()) {
			printf("the head in the ass\n GAME OVER ! \n");
			return TRUE;
		}
	}

	// with an apple
	std::list<GameEntity *> 	apple = map->getApple();
	for (std::list<GameEntity *>::iterator it = apple.begin(); it != apple.end(); it++) {
		if ((*it)->getX() == snake->_head->getX() && (*it)->getY() == snake->_head->getY()) {
			snake->setState("grow");
			snake->upSpeed(1);
			(*it)->setPosition(-1, -1);
		}
	}

	return FALSE;
}

void		Game::input(int keycode)
{
	Snake		*snake;

	snake = getMap()->getSnake();
	if (keycode == KeyEscape)
		this->_shouldExit = TRUE;
	// Pause
	else if (keycode == KeySpace)
		while ((keycode = this->_dlib->getInput()) != KeySpace) {}
	// Snake movements
	else if (keycode == KeyUp)
		snake->move(NORTH);
	else if (keycode == KeyDown)
		snake->move(SOUTH);
	else if (keycode == KeyLeft)
		snake->move(WEST);
	else if (keycode == KeyRight)
		snake->move(EAST);

}

void		Game::update(void)
{
	Map			*map;
	Snake		*snake;

	map = getMap();
	snake = getMap()->getSnake();

	int keycode = 0;
	if ((keycode = this->_dlib->getInput()) != 0) {
		this->input(keycode);
	}
	else
		snake->move(snake->getDirection());

	// Apple generation (at least 1 and more in random)
	std::list<GameEntity *>			apple = map->getApple();
	std::list<GameEntity *>::iterator it = apple.begin();
	if ((*it)->getX() == -1)
		(*it)->setPosition(rand() % map->getWidth(), rand() % map->getHeight());
	if ((Time::getTime() % 100) == 0) {
		while (it != apple.end()) {
			if ((*it)->getX() == -1) {
				(*it)->setPosition(rand() % map->getWidth(), rand() % map->getHeight());
				break;
			}
			it++;
		}
	}
}

void		Game::loop(void)
{
	Map			*map;
	Snake		*snake;

	map = this->getMap();
	snake = new	Snake(map->getWidth() / 2, map->getHeight() / 2);
	map->setSnake(snake);

	srand (time(NULL));

	while (!this->_shouldExit)
	{
		Time::update();

		this->_dlib->draw(map);

		this->_shouldExit = this->collision();

		this->update();

		Time::sleep(200 - snake->getSpeed() * 10);
	}
}
