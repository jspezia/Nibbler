#include "Snake.class.hpp"
#include <list>
#include "GameEntity.class.hpp"

Snake::Snake(void)
{
	return;
}

Snake::Snake(int x, int y) :
	GameEntity(x, y),
	_direction('N'),
	_speed(1),
	_length(3),
	_state("normal")
{
	this->setType("head");

	std::list<GameEntity>	body;

	for (int i = 0; i < this->_length; i++)
		body.push_back(GameEntity(x, y + 1 + i));

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

char	Snake::getDirection(void) const
{
	return this->_direction;
}

void	Snake::setDirection(char const direction)
{
	this->_direction = direction;
}

int			Snake::getSpeed(void) const
{
	return this->_speed;
}

void		Snake::upSpeed(int const speed)
{
	this->_speed += speed;
}

int			Snake::getLength(void) const
{
	return this->_length;
}

void		Snake::upLength(int const length)
{
	this->_length += length;
}

std::string	Snake::getState(void) const
{
	return this->_state;
}

void	Snake::setState(std::string const state)
{
	this->_state = state;
}

void		Snake::move(char const direction)
{
	if (this->_state == "normal")
		this->_body.pop_back();
	else if (this->_state == "grow")
	{
		this->_length += 1;
		this->_state = "normal";
	}
	this->_body.push_front(GameEntity(this->_X, this->_Y));
	//if ((direction == 'N' || direction == 'S') && (this->_direction == 'N' || this->_direction == 'S'))
	if (direction == 'N')
		this->_Y -= 1;
	else if (direction == 'S')
		this->_Y += 1;
	else if (direction == 'E')
		this->_X += 1;
	else if (direction == 'W')
		this->_X -= 1;
	this->_direction = direction;

	std::cout << "Snake as move" << std::endl;
}

Snake		&Snake::operator=(Snake const &rhs)
{
	if (this != &rhs)
	{
		this->_X = rhs.getX();
		this->_Y = rhs.getY();
	}
	return *this;
}

std::ostream		&operator<<(std::ostream &o, Snake const &i)
{
	o << "Snake (" << i.getX() << ","  << i.getY() << ")" << std::endl;
	std::cout << "speed = " << i.getSpeed() << std::endl;
	return o;
}

