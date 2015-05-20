#include <iostream>
#include <string>
#include <stdexcept>
#include "GameEntity.class.hpp"
#include "libft.hpp"


GameEntity::GameEntity()
{
	return;
}

GameEntity::GameEntity(char *height, char *width)
{
	int		h;
	int		w;

	if (!strisdigit(height) || !strisdigit(width))
		throw std::exception();
	h = atoi(height);
	w = atoi(width);
	if (h > 100 || w > 100 || h < 10 || w < 10)
		throw std::exception();
	this->_height = h;
	this->_width = w;

	std::cout << "GameEntity creation, h = " << h << " w = " << w << std::endl;
	return;
}

GameEntity::~GameEntity(void)
{
	return;
}

int GameEntity::getHeight(void) const
{
	return this->_height;
}

int GameEntity::getWidth(void) const
{
	return this->_width;
}

GameEntity		&GameEntity::operator=(GameEntity const &rhs)
{
	if (this != &rhs)
	{
		this->_height = rhs.getHeight();
		this->_width = rhs.getWidth();
	}
	return *this;
}

std::iostream		&operator<<(std::iostream &o, GameEntity const &i)
{
	o << "h = " << i.getHeight() << " w = " << i.getWidth() << std::endl;
	return o;
}

