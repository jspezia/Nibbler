#include <iostream>
#include <math.h>
#include <list>
#include <cstdlib>
#include "Sfml.class.hpp"

Sfml::Sfml(int x, int y) : _x(x), _y(y)
{
	this->_squareSize = (int) fmin(MAX_WIDTH / x, MAX_HEIGHT / y);

	this->_winWidth = this->_squareSize * x;
	this->_winHeight = this->_squareSize * y;
	this->_win = NULL;
}

Sfml::~Sfml(void)
{

}

void			Sfml::init(void)
{
	this->_win = new sf::RenderWindow(sf::VideoMode(this->_winWidth, this->_winHeight), "Nibbler");
	this->_win->setKeyRepeatEnabled(false);
	this->_clear();
}

void			Sfml::close(void)
{
	if (this->_win->isOpen())
		this->_win->close();
}

void			Sfml::draw(Map *map)
{
	if (this->_win->isOpen())
	{
		this->_clear();

		this->_drawGrid();
		this->_drawApple(map->getApple());
		this->_drawSnake(map->getSnake());
		this->_drawScore(map->getScore());

		this->_win->display();
	}
}

void			Sfml::_drawScore(int score)
{
	sf::Text		text;
	sf::Font		font;


	if (!font.loadFromFile("sfml/arial.ttf"))
		printf("unable to open file\n");

	text.setFont(font);
	text.setString("SCORE: " + std::to_string(score));
	text.setCharacterSize(24);
	text.setColor(sf::Color::Black);
	this->_win->draw(text);
}

void			Sfml::_clear(void)
{
	this->_win->clear(sf::Color::Black);
}

void			Sfml::_drawSnake(Snake *snake)
{
	//head
	sf::CircleShape	head(this->_squareSize / 2);
	head.setFillColor(sf::Color(BLACK));

	head.setPosition(snake->_head->getX() * this->_squareSize + 1, snake->_head->getY() * this->_squareSize + 1);
	this->_win->draw(head);

	//eyes
	sf::CircleShape	eyes((this->_squareSize / 2 - 1) / 4);
	eyes.setFillColor(sf::Color(WHITE));

	eyes.setPosition(snake->_head->getX() * this->_squareSize + this->_squareSize * 1 / 4, snake->_head->getY() * this->_squareSize + 1 + this->_squareSize * 1 / 4);
	this->_win->draw(eyes);
	eyes.setPosition(snake->_head->getX() * this->_squareSize + this->_squareSize * 3 / 4 - 1, snake->_head->getY() * this->_squareSize + 1 + this->_squareSize * 1 / 4);
	this->_win->draw(eyes);

	sf::CircleShape	body(this->_squareSize / 2);
	body.setFillColor(sf::Color(BODY_COLOR));

	for (std::list<GameEntity *>::iterator it = snake->_body.begin(); it != snake->_body.end(); it++)
	{
		body.setPosition((*it)->getX() * this->_squareSize + 1, (*it)->getY() * this->_squareSize + 1);
		this->_win->draw(body);
	}
}


void			Sfml::_drawApple(std::list<GameEntity *>		apple)
{
	sf::CircleShape	shape(this->_squareSize / 2, 8);
	sf::CircleShape	leaf(this->_squareSize / 8, 4);
	sf::CircleShape	leaf2(this->_squareSize / 6, 4);
	shape.setFillColor(sf::Color(RED));
	leaf.setFillColor(sf::Color(GREEN));
	leaf2.setFillColor(sf::Color(GREEN));

	for (std::list<GameEntity *>::iterator it = apple.begin(); it != apple.end(); it++)
	{
		shape.setPosition((*it)->getX() * this->_squareSize + 1, (*it)->getY() * this->_squareSize + 1);
		this->_win->draw(shape);
		leaf.setPosition((*it)->getX() * this->_squareSize + 1 + this->_squareSize / 4, (*it)->getY() * this->_squareSize + 1);
		this->_win->draw(leaf);
		leaf2.setPosition((*it)->getX() * this->_squareSize + 1 + this->_squareSize / 2, (*it)->getY() * this->_squareSize + 1);
		this->_win->draw(leaf2);
	}
}

void			Sfml::_drawGrid()
{
	int	margin = 0;
	int size = this->_squareSize - 2 * margin;
	sf::RectangleShape	rect(sf::Vector2f(size * 4, size * 4));

	sf::Texture texture;
	if (!texture.loadFromFile("sfml/texture/grass.png"))
	    rect.setFillColor(sf::Color(NICE_GREEN));
	else
	{
		rect.setTexture(&texture);
		rect.setTextureRect(sf::IntRect(10, 10, 100, 100));
	}
	for (int y = 0; y < this->_y / 4 + 1; y++) {
		for (int x = 0; x < this->_x / 4 + 1; x++) {
			rect.setPosition(margin + x * 4 * this->_squareSize, margin + y * 4 * this->_squareSize);
			this->_win->draw(rect);
		}
	}
}

int				Sfml::getInput(void)
{
	sf::Event event;

	while (this->_win->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				return sf::Keyboard::Escape;
				break;
			case sf::Event::KeyPressed:
				return event.key.code;
				break;
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
