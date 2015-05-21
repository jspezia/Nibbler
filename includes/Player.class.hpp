#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Snake.class.hpp"

enum		e_direction
{
	NORTH = 0, /*    N    */
	EAST  = 1, /*  W + E  */
	SOUTH = 2, /*    S    */
	WEST  = 3  /*         */
};

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
