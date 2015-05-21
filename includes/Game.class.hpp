#ifndef GAME_HPP
# define GAME_HPP

#include <iostream>

class Game
{

public:
	Game(int const width, int const height);
	~Game(void);


private:
	Game(void);
	Game(Game const &ref);
	Game & operator=(Game const & ref);

	/* game size */
	int		_width;
	int		_height;

	/* game map */
	Map &	_map;
};

#endif
