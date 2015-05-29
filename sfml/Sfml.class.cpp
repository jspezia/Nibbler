#include <iostream>
#include <math.h>
#include <Sfml.class.hpp>

Sfml::Sfml(int x, int y) : _x(x), _y(y)
{
	this->_squareWidth = Math.floor(MAX_WIDTH / x);
	this->_squareHeight = Math.floor(MAX_HEIGHT / y);

	this->_winWidth = this->_squareWidth * x;
	this->_winHeight = this->_squareHeight * y;

	this->_init();
}

Sfml::~Sfml(void) {}

extern "C" IGraphic *		init(int width, int height)
{
	return new Sfml(width, height);
}

void			Sfml::_init(void)
{
	this->_win = new sf::RenderWindow(sf::VideoMode(this->_winWidth, this->_winHeight), "Nibbler");
	this->_win->setKeyRepeatEnabled(false);
	this->clear();
}

extern "C" void				destroy(IGraphic * p)
{
	this->_destroy();
	delete p;
}

void			Sfml::_destroy(void)
{
	if (this->_win->isOpen())
		this->_win->close();
}

/* DRAW CALLS */
void			Sfml::draw()
{
	if (this->_win->isOpen())
	{
		//clear window
		this->_clear();

		//draw background (grid)
		this->_drawGrid();

		//draw snake -> (liste de <pos, color>)

	}
}

void			Sfml::_clear(void)
{
	this->_win.clear(sf::Color::Black);
}

void			Sfml::_drawGrid()
{

}


