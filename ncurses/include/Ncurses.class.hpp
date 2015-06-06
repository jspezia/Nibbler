#ifndef NCURSES_CLASS_HPP
# define NCURSES_CLASS_HPP

# include "Map.class.hpp"
# include "IGraphic.class.hpp"
# include <ncurses.h>

class Ncurses : public IGraphic {

	public:
		Ncurses(int width, int height);
		~Ncurses(void);

		void	draw(Map *map);
		int		getInput(void);



	private:
		Ncurses(void);
		Ncurses(Ncurses const & ref);
		Ncurses & operator=(Ncurses const & ref);

		void		_init(void);
		void		_destroy(void);
		void		_drawEdge(void);

		int		_x;
		int		_y;
};

#endif