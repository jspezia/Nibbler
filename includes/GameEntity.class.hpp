#ifndef GameEntity_HPP
# define GameEntity_HPP

#include <iostream>

class GameEntity
{

public:

	GameEntity(char *height, char *width);
	~GameEntity();
	int getHeight(void) const;
	int getWidth(void) const;
	GameEntity		&operator=(GameEntity const &rhs);

protected:

	GameEntity(void);


private:

	int 	_height;
	int		_width;

};

std::ostream		&operator<<(std::ostream &o, GameEntity const &i);

#endif
