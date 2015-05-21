#include <iostream>
#include <string>
#include <stdexcept>

#include "Map.class.hpp"
#include "Lib.hpp"

Map::Map(int width, int height) : _width(width), _height(height)
{
	std::cout << "Map creation" << std::endl;
	std::cout << this->printHW() << std::endl;
	return;
}

Map::~Map(void)
{
	return;
}

int Map::getHeight(void) const
{
	return this->_height;
}

int Map::getWidth(void) const
{
	return this->_width;
}

Map			&Map::operator=(Map const &rhs)
{
	if (this != &rhs)
	{
		this->_height = rhs.getHeight();
		this->_width = rhs.getWidth();
	}
	return *this;
}

std::string		Map::printHW(void) const
{
	std::string		position;

	position = "Height = " + std::to_string(this->_height) + " Width = " + std::to_string(this->_width);
	return position;
}

