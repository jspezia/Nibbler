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
void			Sfml::draw(Snake *snake)
{
	if (this->_win->isOpen())
	{
		// printf("Draw call\n");
		//clear window
		this->_clear();

		//draw background (grid)
		this->_drawGrid();

		//draw snake -> (liste de <pos, color>)
		this->_drawSnake(snake);

		//display
		this->_win->display();
	}
}

void			Sfml::_clear(void)
{
	this->_win->clear(sf::Color::Black);
}

void			Sfml::_drawSnake(Snake *snake)
{
	printf("snake position = %dx, %dy\n", snake->_head->getX(), snake->_head->getY());

//head
	sf::CircleShape	shape(this->_squareSize / 2 - 1);
	shape.setFillColor(sf::Color(BLACK));

	shape.setPosition(snake->_head->getX() * this->_squareSize + 1, snake->_head->getY() * this->_squareSize + 1);
	this->_win->draw(shape);
//eyes
	sf::CircleShape	eyes(1.f);
	eyes.setFillColor(sf::Color(WHITE));
	eyes.setPosition(snake->_head->getX() * this->_squareSize + this->_squareSize * 1 / 4, snake->_head->getY() * this->_squareSize + 1 + this->_squareSize * 1 / 4);
	this->_win->draw(eyes);
	eyes.setPosition(snake->_head->getX() * this->_squareSize + this->_squareSize * 3 / 4 - 1, snake->_head->getY() * this->_squareSize + 1 + this->_squareSize * 1 / 4);
	this->_win->draw(eyes);


	int		i = 1;
	shape.setFillColor(sf::Color(RED));
	for (std::list<GameEntity *>::iterator it = snake->_body.begin(); it != snake->_body.end(); it++)
	{
		shape.setPosition((*it)->getX() * this->_squareSize + 1, (*it)->getY() * this->_squareSize + 1);
		this->_win->draw(shape);
		
		std::cout << "body nb " << i << " in position ";
		std::cout << "x = " << (*it)->getY() << " y = " << (*it)->getX() << std::endl;
		i++;
	}
}

void			Sfml::_drawGrid()
{
	int	margin = 1; //px
	int size = this->_squareSize - 2 * margin;
	sf::RectangleShape	rect(sf::Vector2f(size, size));
	rect.setFillColor(sf::Color(GREEN));

	for (int y = 0; y < this->_y; y++) {
		for (int x = 0; x < this->_x; x++) {
			rect.setPosition(margin + x * this->_squareSize, margin + y * this->_squareSize);

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
