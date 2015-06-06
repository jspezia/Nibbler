# include "Ncurses.class.hpp"

Ncurses::Ncurses(int x, int y) : _x(x), _y(y)
{
	this->_init();
}

Ncurses::~Ncurses(void) {
	this->_destroy();
}

void		Ncurses::_init(void)
{
	initscr();
}

void		Ncurses::_destroy(void)
{
	endwin();
}

void		Ncurses::_drawEdge()
{
	//axe vertical
	for (int x = 0; x != this->_x + 2; x++) {
		mvprintw(x, 0, "+");
		mvprintw(x, this->_y + 2, "+");
	}
	// axe horizontal
	for (int y = 0; y != this->_y + 2; y++) {
		mvprintw(0, y, "+");
		mvprintw(this->_x + 2, y, "+");
	}
}

void		Ncurses::draw(Map *map)
{
	(void)map;

	clear();
	this->_drawEdge();
	refresh();
	while (1) {}

}

int			Ncurses::getInput(void)
{
	return 0;
}

extern "C" IGraphic *		init(int width, int height)
{
	return new Ncurses(width, height);
}

extern "C" void				destroy(IGraphic * p)
{
	delete p;
}