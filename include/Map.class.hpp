#ifndef Map_HPP
# define Map_HPP

# include "Snake.class.hpp"

#include <iostream>

class Map
{

public:
	Map(int width, int height);
	~Map();

	int 			getHeight(void) const;
	int 			getWidth(void) const;
	std::string		printHW(void) const;

	void			setSnake(Snake *snake);
	Snake			*getSnake(void) const;

protected:

private:
	Map(void);
	Map &	operator=(Map const & ref);

	Snake	*_snake;
	int		_width;
	int 	_height;
};

std::ostream		&operator<<(std::ostream &o, Map const &i);

#endif
