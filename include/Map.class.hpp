#ifndef Map_HPP
# define Map_HPP

# include "Snake.class.hpp"

#include <iostream>

class Map
{

public:
	Map(int width, int height);
	~Map();

	int 						getHeight(void) const;
	int 						getWidth(void) const;
	int 						getScore(void) const;
	Snake						*getSnake(void) const;
	std::list<GameEntity *>		getApple(void) const;

	void						setSnake(Snake *snake);
	void						setScore(int score);

protected:

private:
	Map(void);
	Map &	operator=(Map const & ref);

	std::list<GameEntity *>		_apple;
	Snake						*_snake;
	int							_width;
	int 						_height;

	int							_score;
};

std::ostream		&operator<<(std::ostream &o, Map const &i);

#endif
