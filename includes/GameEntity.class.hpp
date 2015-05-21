#ifndef GAMEENTITY_HPP
# define GAMEENTITY_HPP

#include <iostream>

class GameEntity
{

public:

	GameEntity(void);
	GameEntity(int x, int y);
	GameEntity(GameEntity const &src);
	~GameEntity();
	int 		getX(void) const;
	int 		getY(void) const;

	GameEntity		&operator=(GameEntity const &rhs);

protected:
	int		_X;
	int		_Y;

private:

};

std::ostream	&operator<<(std::ostream &o, GameEntity const &i);

#endif
