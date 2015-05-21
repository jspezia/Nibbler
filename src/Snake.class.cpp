#include "Snake.class.hpp"

Snake::Snake(void)
{
	return;
}

Snake::Snake(int x, int y) :
	GameEntity(x, y),
	_speed(1)
{
	return;
}

Snake::Snake(Snake const &src)
{
	*this = src;
}

Snake::~Snake(void)
{
	return;
}

void		Snake::upSpeed(int const speed)
{
	this->_speed += speed;
}

int			Snake::getSpeed(void) const
{
	return this->_speed;
}

void		Snake::setPosition(int const x, int const y)
{
	this->_X = x;
	this->_Y = y;
	std::cout << "Snake as move" << std::endl;
}

Snake		&Snake::operator=(Snake const &rhs)
{
	if (this != &rhs)
		this->_X = rhs.getX();
		this->_Y = rhs.getY();
	return *this;
}

std::ostream		&operator<<(std::ostream &o, Snake const &i)
{
	o << "Snake (" << i.getX() << ","  << i.getY() << ")" << std::endl;
	std::cout << "speed = " << i.getSpeed() << std::endl;
	return o;
}

