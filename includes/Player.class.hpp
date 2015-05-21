#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <iostream>

class Player
{

public:
	Player(void);
	~Player();

protected:

private:
	Player(Player const & ref);
	Player &	operator=(Player const & ref);

};

#endif
