#include "Game.class.hpp"
#include "Player.class.hpp"
#include "Map.class.hpp"
#include "Time.class.hpp"
#include "DynamicLibHandler.class.hpp"
#include "KeyValue.hpp"
#include "Lib.hpp"
#include "Snake.class.hpp"
#include "GameEntity.class.hpp"
#include "nibbler.h"
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
void		Game::init(std::string dlib_path)
{
	this->_setDLib(dlib_path);
	this->_score = 0;
}

void		Game::_setDLib(std::string dlib_path)
{
	printf("lib loaded: %s\n", dlib_path.c_str());
	this->_currentDLib = dlib_path;
	DynamicLibHandler::instance().setHandle(dlib_path, this->_width, this->_height);
	this->_dlib = DynamicLibHandler::instance().getLib();
}

int			Game::_handleCollisions(void)
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

			this->_score++;
			map->setScore(this->_score);
		}
	}

	return FALSE;
}

void		Game::_handleMovementInputs(int key)
{
	int		direction;
	Snake		*snake;

	snake = getMap()->getSnake();

	if (key == KeyUp)
		direction = NORTH;
	else if (key == KeyDown)
		direction = SOUTH;
	else if (key == KeyLeft)
		direction = WEST;
	else if (key == KeyRight)
		direction = EAST;
	else
		return ;

	snake->move(direction);
}

void		Game::_handleLibSwichInputs(int key)
{
	std::string		lib;

	if (key == KeyNum1)
		lib = DLIB_NCURSES;
	else if (key == KeyNum2)
		lib = DLIB_SFML;
	else if (key == KeyNum3)
		lib = DLIB_GLFW;
	else
		return ;

	if (lib == this->_currentDLib)
		return ;

	this->_setDLib(lib);
}

void		Game::_handleInputs(int keycode)
{
	// Quit
	if (keycode == KeyEscape)
		this->_shouldExit = TRUE;

	// Pause
	if (keycode == KeySpace)
		while ((keycode = this->_dlib->getInput()) != KeySpace) {}

	// Snake movements
	this->_handleMovementInputs(keycode);

	// Lib Swiches
	this->_handleLibSwichInputs(keycode);
}

void		Game::update(void)
{
	Map			*map;
	Snake		*snake;

	map = getMap();
	snake = getMap()->getSnake();

	int keycode = 0;
	if ((keycode = this->_dlib->getInput()) != 0) {
		this->_handleInputs(keycode);
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

	srand(time(NULL));
	while (!this->_shouldExit)
	{
		Time::update();

		this->_dlib->draw(map);

		this->_shouldExit = this->_handleCollisions();

		this->update();

		Time::sleep(200 - snake->getSpeed() * 10);
	}
	printf("Final score: %d\n", this->_score);
}
