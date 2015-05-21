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
	void		setType(std::string const type);
	std::string	getType(void) const;
	void		setPosition(int const x, int const y);

	GameEntity		&operator=(GameEntity const &rhs);

protected:
	int			_X;
	int			_Y;
	std::string	_type;

private:

};

std::ostream	&operator<<(std::ostream &o, GameEntity const &i);

#endif
