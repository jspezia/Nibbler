#ifndef GAME_HPP
# define GAME_HPP

# include <iostream>
# include "Map.class.hpp"
# include "Player.class.hpp"
# include "IGraphic.class.hpp"

# define MIN_WIDTH		10
# define MAX_WIDTH		100
# define MIN_HEIGHT		10
# define MAX_HEIGHT		100

class Game
{

public:
	Game(int const width, int const height);
	~Game(void);

	Map *		getMap(void) const;
	Player *	getPlayer(void) const;

	int			collision(void);
	void		input(int keycode);
	void		update(void);
	void		init(std::string dlib_path);
	void		loop(void);

private:
	Game(void);
	Game(Game const & ref);
	Game & operator=(Game const & ref);

	/* game size */
	int			_width;
	int			_height;

	/* game map */
	Map *		_map;

	/* player */
	Player *	_player;

	/* graphic dynamic lib */
	IGraphic *	_dlib;

	/* shutdown condition */
	bool		_shouldExit;
};

#endif
