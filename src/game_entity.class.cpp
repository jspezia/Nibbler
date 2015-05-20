#include "game_entity.class.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <locale>

game_entity::game_entity()
{
	return;
}

game_entity::game_entity(char *height, char *width)
{
	int		h;
	int		w;

	h = atoi(height);
	w = atoi(width);
	if (h > 100 || w > 100 || h < 1 || w < 1)
		throw std::exception();
	this->_height = h;
	this->_width = w;

	std::cout << "game_entity creation, h = " << h << " w = " << w << std::endl;
	return;
}

game_entity::~game_entity(void)
{
	return;
}

int game_entity::getHeight(void) const
{
	return this->_height;
}

int game_entity::getWidth(void) const
{
	return this->_width;
}

game_entity		&game_entity::operator=(game_entity const &rhs)
{
	if (this != &rhs)
	{
		this->_height = rhs.getHeight();
		this->_width = rhs.getWidth();
	}
	return *this;
}

std::iostream		&operator<<(std::iostream &o, game_entity const &i)
{
	o << "h = " << i.getHeight() << " w = " << i.getWidth() << std::endl;
	return o;
}

