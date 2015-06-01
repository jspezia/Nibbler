#include <iostream>
#include <string>
#include <stdexcept>

#include "Map.class.hpp"
#include "Lib.hpp"

Map::Map(int width, int height) : _width(width), _height(height)
{
	std::cout << "Map creation" << std::endl;
	std::cout << this->printHW() << std::endl;


	for (int i = 0; i < 5; i++)
	{
		GameEntity *	newApple;

		newApple = new GameEntity(-1, -1, "apple");
		if (newApple)
			this->_apple.push_back(newApple);
	}

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

/* SETTER */

void			Map::setSnake(Snake *snake)
{
	this->_snake = snake;
}

Map &		Map::operator=(Map const &rhs)
{
	if (this != &rhs)
	{
		this->_height = rhs.getHeight();
		this->_width = rhs.getWidth();
	}
	return *this;
}

// void			Map::addApple(int const x, int const y)
// {
// 	GameEntity		*newApple;

// 	newApple = new GameEntity(x, y, "apple");

// 	this->_apple.push_back(newApple);
// }



std::string		Map::printHW(void) const
{
	std::string		position;

	position = "Height = " + std::to_string(this->_height) + " Width = " + std::to_string(this->_width);
	return position;
}

