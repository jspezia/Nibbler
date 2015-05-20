#ifndef GAME_ENTITY_HPP
# define GAME_ENTITY_HPP

#include <iostream>

class game_entity
{

public:

	game_entity(char *height, char *width);
	~game_entity();
	int getHeight(void) const;
	int getWidth(void) const;
	game_entity		&operator=(game_entity const &rhs);

protected:

	game_entity(void);


private:

	int 	_height;
	int		_width;

};

std::ostream		&operator<<(std::ostream &o, game_entity const &i);

#endif
