#include <iostream>
#include <string>
#include <stdexcept>

#include "Map.class.hpp"
#include "Lib.hpp"


Map::Map(int width, int height) : _width(width), _height(height)
{
	std::cout << "Map creation" << std::endl;

	// init Apples
	for (int i = 0; i < 5; i++)
	{
		GameEntity *	newApple;

		newApple = new GameEntity(-1, -1, "apple");
		if (newApple)
			this->_apple.push_back(newApple);
	}

	// // init Snake
	// this->_snake = new	Snake(width / 2, height / 2);

	return;
}

Map::~Map(void)
{
	return;
}

/* GETTER */

int			Map::getHeight(void) const
{
	return this->_height;
}

int			Map::getWidth(void) const
{
	return this->_width;
}

Snake			*Map::getSnake(void) const
{
	return this->_snake;
}

std::list<GameEntity *>			Map::getApple(void) const
{
	return this->_apple;
}

/* SETTER */

void			Map::setSnake(Snake *snake)
{
	this->_snake = snake;
}



