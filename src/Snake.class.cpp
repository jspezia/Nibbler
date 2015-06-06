#include <list>
#include "Snake.class.hpp"
#include "Player.class.hpp"
#include "GameEntity.class.hpp"

Snake::Snake(int x, int y) : _direction(NORTH), _speed(1), _state("normal")
{
	this->init(x, y);
}

Snake::~Snake(void) {}

void		Snake::init(int x, int y)
{
	/* init head */
	this->_head = new GameEntity(x, y, "head");

	/* init body parts */
	for (int i = 0; i < 4 - 1; i++)
	{
		GameEntity *	newBodyPart;

		newBodyPart = new GameEntity(x, y + 1 + i, "body");
		if (newBodyPart)
			this->_body.push_back(newBodyPart);
	}
}

/* GETTERS */
int			Snake::getDirection(void) const
{
	return this->_direction;
}

int			Snake::getSpeed(void) const
{
	return this->_speed;
}

std::string	Snake::getState(void) const
{
	return this->_state;
}

/* SETTERS */
void		Snake::setDirection(int const direction)
{
	this->_direction = direction;
}

void		Snake::setState(std::string const state)
{
	this->_state = state;
}

void		Snake::upSpeed(int const speed)
{
	this->_speed += speed;
}

void		Snake::move(int const direction)
{
	if (this->_state == "normal")
		this->_body.pop_back();
	else
		this->_state = "normal";

	GameEntity *	newBodyPart;
	newBodyPart = new GameEntity(this->_head->_x, this->_head->_y);
	this->_body.push_front(newBodyPart);

	if (direction == NORTH){
		if (this->_direction != SOUTH){
			this->_head->_y -= 1;
			this->_direction = direction;
		}
		else
			this->_head->_y += 1;
	}
	else if (direction == SOUTH)
	{
		if (this->_direction != NORTH) {
			this->_head->_y += 1;
			this->_direction = direction;
		}
		else
			this->_head->_y -= 1;
	}
	else if (direction == EAST)
	{
		if (this->_direction != WEST) {
			this->_head->_x += 1;
			this->_direction = direction;
		}
		else
			this->_head->_x -= 1;
	}
	else if (direction == WEST)
	{
		if (this->_direction != EAST) {
			this->_head->_x -= 1;
			this->_direction = direction;
		}
		else
			this->_head->_x += 1;
	}
}












