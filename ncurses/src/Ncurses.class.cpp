# include "Ncurses.class.hpp"
# include "KeyValue.hpp"

Ncurses::Ncurses(int x, int y) : _x(x), _y(y)
{

}

Ncurses::~Ncurses(void)
{

}

void		Ncurses::init(void)
{
	initscr();
	noecho();
	keypad(stdscr, 1);
	start_color();
	init_pair(1,COLOR_BLACK,COLOR_GREEN);
	init_pair(2,COLOR_RED,COLOR_GREEN);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_WHITE);
	init_pair(5,COLOR_GREEN,COLOR_WHITE);
	init_pair(6,COLOR_BLACK,COLOR_CYAN);
	attrset(COLOR_PAIR(1));
}

void		Ncurses::close(void)
{
	endwin();
}

void		Ncurses::_drawEdge()
{
	//map
	for (int x = 0; x != this->_x + 1; x++) {
		for (int y = 0; y != this->_y + 1; y ++) {
			mvprintw(x, y, " ");
		}
	}
	//axe vertical
	for (int x = 0; x != this->_x + 1; x++) {
		mvprintw(x, 0, "+");
		mvprintw(x, this->_y + 1, "+");
	}
	// axe horizontal
	for (int y = 0; y != this->_y + 1; y++) {
		mvprintw(0, y, "+");
		mvprintw(this->_x + 1, y, "+");
	}
	mvprintw(this->_x + 1, this->_y + 1, "+");
}

void		Ncurses::_drawApple(std::list<GameEntity *>		apple)
{
	attrset(COLOR_PAIR(2));
	for (std::list<GameEntity *>::iterator it = apple.begin(); it != apple.end(); it++) {
		if ((*it)->getY() != -1 and (*it)->getX() != -1)
			mvprintw((*it)->getY() + 1, (*it)->getX() + 1, "o");
	}
	attrset(COLOR_PAIR(1));
}

void		Ncurses::_drawSnake(Snake *snake)
{
	attrset(COLOR_PAIR(4));
	mvprintw(snake->_head->getY() + 1, snake->_head->getX() + 1, "Y");
	attrset(COLOR_PAIR(5));
	for (std::list<GameEntity *>::iterator it = snake->_body.begin(); it != snake->_body.end(); it++) {
		mvprintw((*it)->getY() + 1, (*it)->getX() + 1, "o");
	}
	attrset(COLOR_PAIR(1));
}

void		Ncurses::_drawObstacles(std::list<GameEntity *> obst)
{

	attrset(COLOR_PAIR(6));
	for (std::list<GameEntity *>::iterator it = obst.begin(); it != obst.end(); it++) {
		mvprintw((*it)->getY() + 1, (*it)->getX() + 1, "X");
	}
	attrset(COLOR_PAIR(1));



}

void		Ncurses::_drawScore(int score)
{
	std::string		result;

	result = "Score: " + std::to_string(score);
	attrset(COLOR_PAIR(3));
	mvprintw(this->_x + 4, 0, (char*)result.c_str());
	attrset(COLOR_PAIR(1));
}

void		Ncurses::draw(Map *map)
{
	clear();
	this->_drawEdge();
	this->_drawApple(map->getApple());
	this->_drawObstacles(map->getObstacles());
	this->_drawSnake(map->getSnake());
	this->_drawScore(map->getScore());
	refresh();
}

int			Ncurses::getInput(void)
{
	int		c;
	if ((c = getch()) != ERR) {
		switch (c)
		{
			case KEY_DOWN: return(KeyDown);  break;
			case KEY_UP: return(KeyUp);  break;
			case KEY_RIGHT: return(KeyRight);  break;
			case KEY_LEFT:  return(KeyLeft);  break;
			case KEY_BACKSPACE: return(KeySpace); break;
			case 27: return(KeyEscape);
			case KEY_F(1): return(KeyF1); break;
			case KEY_F(2): return(KeyF2); break;
			case KEY_F(3): return(KeyF3); break;
		}
	}
	return (0);
}

extern "C" IGraphic *		init(int width, int height)
{
	return new Ncurses(width, height);
}

extern "C" void				destroy(IGraphic * p)
{
	delete p;
}
