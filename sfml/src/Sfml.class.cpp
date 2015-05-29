#include <iostream>
#include <math.h>
#include "Sfml.class.hpp"

Sfml::Sfml(int x, int y) : _x(x), _y(y)
{
	this->_squareSize = (int) fmin(MAX_WIDTH / x, MAX_HEIGHT / y);

	this->_winWidth = this->_squareSize * x;
	this->_winHeight = this->_squareSize * y;

	this->_init();
}

Sfml::~Sfml(void) {}


void			Sfml::_init(void)
{
	this->_win = new sf::RenderWindow(sf::VideoMode(this->_winWidth, this->_winHeight), "Nibbler");
	this->_win->setKeyRepeatEnabled(false);
	this->_clear();
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
		printf("Draw call\n");
		//clear window
		this->_clear();

		//draw background (grid)
		this->_drawGrid();

		//draw snake -> (liste de <pos, color>)

		//display
		this->_win->display();
	}
}

void			Sfml::_clear(void)
{
	this->_win->clear(sf::Color::Black);
}

void			Sfml::_drawGrid()
{
	this->_win->clear(sf::Color(GREEN)); // full background
	sf::Color		color = sf::Color::Black;

	//vertical
	for (int x = 0; x < this->_x; x++)
	{
		int posX = x * this->_squareSize;
		sf::Vertex line[] =
		{
		    sf::Vertex(sf::Vector2f(posX, 0), color),
		    sf::Vertex(sf::Vector2f(posX, this->_winHeight), color)
		};
		this->_win->draw(line, 2, sf::Lines);
	}

	//horizontal
	for (int y = 0; y < this->_y; y++)
	{
		int posY = y * this->_squareSize;
		sf::Vertex line[] =
		{
		    sf::Vertex(sf::Vector2f(0, posY), color),
		    sf::Vertex(sf::Vector2f(this->_winWidth, posY), color)
		};
		this->_win->draw(line, 2, sf::Lines);
	}
}

extern "C" IGraphic *		init(int width, int height)
{
	return new Sfml(width, height);
}

extern "C" void				destroy(IGraphic * p)
{
	delete p;
}
