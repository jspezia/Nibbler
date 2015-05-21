#include "GameEntity.class.hpp"

GameEntity::GameEntity(int x, int y) : _x(x), _y(y)
{
}

GameEntity::GameEntity(int x, int y, std::string type) : _x(x), _y(y), _type(type)
{
}

GameEntity::~GameEntity(void) {}

/* GETTERS */
int				GameEntity::getX(void) const
{
	return this->_x;
}

int				GameEntity::getY(void) const
{
	return this->_y;
}

std::string		GameEntity::getType(void) const
{
	return this->_type;
}

/* SETTERS */
void			GameEntity::setType(std::string const type)
{
	this->_type = type;
}

void			GameEntity::setPosition(int const x, int const y)
{
	this->_x = x;
	this->_y = y;
}

std::ostream &		operator<<(std::ostream &o, GameEntity const &i)
{
	o << "object in x = " << i.getX() << " y = " << i.getY() << std::endl;
	return o;
}

