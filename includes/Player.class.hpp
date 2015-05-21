#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Snake.class.hpp"

class Player
{

public:
	Player(int x, int y);
	~Player();

	void		init();

protected:

private:
	Player(void);
	Player(Player const & ref);
	Player &	operator=(Player const & ref);

	Snake *		_snake;
};

#endif
