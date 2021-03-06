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
	this->_dlib = NULL;
	this->_isPaused = FALSE;
}


Game::~Game(void)
{
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
	printf("Loading library: %s\n", dlib_path.c_str());

	if (this->_dlib)
	{
		this->_dlib->close();
	}

	this->_currentDLib = dlib_path;
	try {
		DynamicLibHandler::instance().setHandle(dlib_path, this->_width, this->_height);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
		exit(0);
	}

	this->_dlib = DynamicLibHandler::instance().getLib();

	this->_dlib->init();
}

void		Game::_handleCollisions(void)
{
	Snake		*snake;
	Map			*map;

	map = getMap();
	snake = map->getSnake();

	// with the edge
	if (snake->_head->getX() < 0  || snake->_head->getX() > map->getWidth() - 1
		|| snake->_head->getY() < 0 || snake->_head->getY() > map->getHeight() - 1) {
		printf("GAME OVER! (bang the wall)\n");
		this->_shouldExit = TRUE;
		return ;
	}

	// with himself
	for (std::list<GameEntity *>::iterator it = snake->_body.begin(); it != snake->_body.end(); it++) {
		if ((*it)->getX() == snake->_head->getX() && (*it)->getY() == snake->_head->getY()) {
			printf("GAME OVER! (the head in the ass)\n");
			this->_shouldExit = TRUE;
			return ;
		}
	}

	// with an obstacle
	std::list<GameEntity *> 	obst = map->getObstacles();
	for (std::list<GameEntity *>::iterator it = obst.begin(); it != obst.end(); it++) {
		if ((*it)->getX() == snake->_head->getX() && (*it)->getY() == snake->_head->getY()) {
			printf("GAME OVER! (hit an obstacle)\n");
			this->_shouldExit = TRUE;
			return ;
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

	// with bonus
	GameEntity *	bonus = map->getBonus();
	if (bonus->getX() == snake->_head->getX() && bonus->getY() == snake->_head->getY()) {
		snake->setState("grow");
		bonus->setPosition(-1, -1);

		this->_score += 10;
		map->setScore(this->_score);
	}
}

void		Game::_handleMovementInputs(int key)
{
	int		direction;
	Snake		*snake;

	snake = this->getMap()->getSnake();

	switch (key) {
		case KeyUp:		direction = NORTH;	break;
		case KeyDown:	direction = SOUTH;	break;
		case KeyLeft:	direction = WEST;	break;
		case KeyRight:	direction = EAST;	break;
		default: return;
	}

	snake->setDirection(direction);
}

void		Game::_handleLibSwichInputs(int key)
{
	std::string		lib;

	switch (key) {
		case KeyNum1: lib = DLIB_NCURSES;	break;
		case KeyNum2: lib = DLIB_SFML;		break;
		case KeyNum3: lib = DLIB_GLFW;		break;
		default: return;
	}

	if (lib == this->_currentDLib)
		return;

	this->_setDLib(lib);
}

void		Game::_handleInputs(int keycode)
{
	// Quit
	if (keycode == KeyEscape)
	{
		printf("QUIT\n");
		exit(EXIT_SUCCESS);
	}

	// Pause
	if (keycode == KeySpace)
		this->_isPaused = !this->_isPaused;

	// Snake movements
	if (!this->_isPaused)
		this->_handleMovementInputs(keycode);

	// Lib Swiches
	this->_handleLibSwichInputs(keycode);
}

bool		isPositionOccupiedBy(std::list<GameEntity *> obst, int x, int y)
{
	std::list<GameEntity *>::iterator	it = obst.begin();
	while (it != obst.end()) {
		if ((*it)->getX() == x && (*it)->getY() == y) {
			printf("TRUE\n");
			return TRUE;
		}
		it++;
	}
	return FALSE;
}

void		Game::update(void)
{
	Map			*map;
	Snake		*snake;

	map = this->getMap();
	snake = map->getSnake();

	snake->move();

	int		x;
	int		y;
	std::list<GameEntity *>				apple = map->getApple();
	std::list<GameEntity *>::iterator	it = apple.begin();
	if ((*it)->getX() == -1) {
		x = rand() % map->getWidth();
		y = rand() % map->getHeight();

		while (isPositionOccupiedBy(map->getObstacles(), x, y) || isPositionOccupiedBy(map->getApple(), x, y) == TRUE) {
			x = rand() % map->getWidth();
			y = rand() % map->getHeight();
		}
		(*it)->setPosition(x, y);
	}

	// BONUS
	static int		timeout = 0;
	GameEntity *	bonus = map->getBonus();
	int ts = Time::getTime();

	if (timeout && ts > timeout) {
		bonus->setPosition(-1, -1);
		timeout = 0;
	}

	if (bonus->getX() == -1 && !(ts % 100)) {
		x = rand() % map->getWidth();
		y = rand() % map->getHeight();

		while (isPositionOccupiedBy(map->getObstacles(), x, y) || isPositionOccupiedBy(map->getApple(), x, y) == TRUE) {
			x = rand() % map->getWidth();
			y = rand() % map->getHeight();
		}

		timeout = ts + (map->getWidth() * 1000 / 4);
		bonus->setPosition(x, y);
	}

	this->_handleCollisions();
}

void		Game::loop(void)
{
	Map			*map;
	Snake		*snake;

	map = this->getMap();
	snake = new	Snake(map->getWidth() / 2, map->getHeight() / 2);
	map->setSnake(snake);

	while (!this->_shouldExit)
	{
		Time::update();

		/* events */
		this->_handleInputs(this->_dlib->getInput());

		/* update */
		if (!this->_isPaused)
			this->update();

		/* refresh display */
		this->_dlib->draw(map);

		Time::sleep(200 - snake->getSpeed() * 10);
	}
	this->_dlib->close();

	printf("Final score: %d\n", this->_score);
}
