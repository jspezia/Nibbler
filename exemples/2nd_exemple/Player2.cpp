#include "Player2.hpp"

Player2::Player2(std::string name) :
	_score(0),
	_name(name)
{
}

Player2::~Player2(void)
{
}

std::string		Player2::getName(void) const
{
	return this->_name;
}

int				Player2::getScore(void) const
{
	return this->_score;
}

void			Player2::markPoint(void)
{
	this->_score++;
}

void			Player2::announces(void) const
{
	std::cout << "blablabla " << this->_name << " blablabla ";
	std::cout << this->_score << " blablabla" << std::endl;
}

Player2			*createPlayer(const std::string &name)
{
	return new Player2(name);
}

void			deletePlayer(Player2 *player2)
{
	delete player2;
}
