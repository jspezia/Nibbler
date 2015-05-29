#include <iostream>
#include <math.h>
#include <list>
// #include <algorithm>
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
		// printf("Draw call\n");
		//clear window
		this->_clear();

		//draw background (grid)
		this->_drawGrid();

		//draw snake -> (liste de <pos, color>)
		// this->_drawSnake(bodyPartsList);

		//display
		this->_win->display();
	}
}

void			Sfml::_clear(void)
{
	this->_win->clear(sf::Color::Black);
}

void			Sfml::_drawSnake()
{
	// ...
}

void			Sfml::_drawGrid()
{
	int	margin = 1; //px

	for (int y = 0; y < this->_y; y++) {
		for (int x = 0; x < this->_x; x++) {
			int size = this->_squareSize - 2 * margin;
			sf::RectangleShape	rect(sf::Vector2f(size, size));
			rect.setPosition(margin + x * this->_squareSize, margin + y * this->_squareSize);
			rect.setFillColor(sf::Color(GREEN));

			this->_win->draw(rect);
		}

	}
}

/* INPUT EVENTS */
int				Sfml::getInput(void)
{
	sf::Event event;

	while (this->_win->pollEvent(event))
	{
		// on regarde le type de l'évènement...
		switch (event.type)
		{
			case sf::Event::Closed:
				this->_win->close();
				return sf::Keyboard::Escape;
				break;

			case sf::Event::KeyPressed:
				// printf("code: %d\n", event.key.code);
				return event.key.code;
				break;

			// on ne traite pas les autres types d'évènements
			default:
				break;
		}
	}
	return (0);
}


extern "C" IGraphic *		init(int width, int height)
{
	return new Sfml(width, height);
}

extern "C" void				destroy(IGraphic * p)
{
	delete p;
}
