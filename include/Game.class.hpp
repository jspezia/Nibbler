#ifndef GAME_HPP
# define GAME_HPP

# include <iostream>
# include "Map.class.hpp"
# include "Player.class.hpp"
# include "IGraphic.class.hpp"

# define MIN_WIDTH		10
# define MAX_WIDTH		50
# define MIN_HEIGHT		10
# define MAX_HEIGHT		50

class Game
{

public:
	Game(int const width, int const height);
	~Game(void);

	Map *		getMap(void) const;
	Player *	getPlayer(void) const;

	void		init(std::string dlib_path);
	void		loop(void);
	void		update(void);

private:
	Game(void);
	Game(Game const & ref);
	Game & operator=(Game const & ref);

	void	_setDLib(std::string dlib_path);

	void	_handleCollisions(void);

	void	_handleMovementInputs(int key);
	void	_handleLibSwichInputs(int key);
	void	_handleInputs(int keycode);

	/* game size */
	int			_width;
	int			_height;

	/* game map */
	Map *		_map;

	/* player */
	Player *	_player;

	/* graphic dynamic lib */
	IGraphic *	_dlib;
	std::string	_currentDLib;

	int			_score;

	bool		_isPaused;

	/* shutdown condition */
	bool		_shouldExit;


};

#endif
