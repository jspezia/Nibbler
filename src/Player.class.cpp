#include "Player.class.hpp"
#include "Snake.class.hpp"
#include "nibbler.h"

Player::Player(int x, int y)
{
	this->_snake = new Snake(x, y);
}

Player::~Player(void) {}

void		Player::init(void)
{
}

Snake *		Player::getSnake()
{
	return this->_snake;
}
