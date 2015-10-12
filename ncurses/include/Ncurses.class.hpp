#ifndef NCURSES_CLASS_HPP
# define NCURSES_CLASS_HPP

# include "Map.class.hpp"
# include "IGraphic.class.hpp"
# include <ncurses.h>

class Ncurses : public IGraphic {

	public:
		Ncurses(int width, int height);
		~Ncurses(void);

		void	init(void);
		void	draw(Map *map);
		int		getInput(void);
		void	close(void);

		WINDOW	*_win;
	private:
		Ncurses(void);
		Ncurses(Ncurses const & ref);
		Ncurses & operator=(Ncurses const & ref);


		void		_drawSnake(Snake *snake);
		void		_drawScore(int score);
		void		_drawApple(std::list<GameEntity *>		apple);
		void		_drawObstacles(std::list<GameEntity *>	obst);

		void		_drawEdge(void);

		int		_x;
		int		_y;
};

#endif
