#include "GameEntity.class.hpp"

GameEntity::GameEntity(void)
{
	return;
}

GameEntity::GameEntity(int x, int y) :
	_X(x),
	_Y(y)
{
	return;
}

GameEntity::GameEntity(GameEntity const &src)
{
	*this = src;
}

GameEntity::~GameEntity(void)
{
	return;
}

int GameEntity::getX(void) const
{
	return this->_X;
}

int GameEntity::getY(void) const
{
	return this->_Y;
}

void		GameEntity::setType(std::string const type)
{
	this->_type = type;
}

std::string		GameEntity::getType(void) const
{
	return this->_type;
}

void		GameEntity::setPosition(int const x, int const y)
{
	this->_X = x;
	this->_Y = y;
}

GameEntity		&GameEntity::operator=(GameEntity const &rhs)
{
	if (this != &rhs)
	{
		this->_X = rhs.getX();
		this->_Y = rhs.getY();
	}
	return *this;
}

std::ostream		&operator<<(std::ostream &o, GameEntity const &i)
{
	o << "object in x = " << i.getX() << " y = " << i.getY() << std::endl;
	return o;
}

