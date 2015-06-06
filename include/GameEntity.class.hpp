#ifndef GAMEENTITY_HPP
# define GAMEENTITY_HPP

#include <iostream>

class GameEntity
{

public:
	GameEntity(int x, int y);
	GameEntity(int x, int y, std::string type);
	GameEntity(void);
	~GameEntity();

	int 			getX(void) const;
	int 			getY(void) const;
	std::string		getType(void) const;
	void			setPosition(int const x, int const y);

	int				_x;
	int				_y;
	std::string		_type;

protected:

private:
	GameEntity(GameEntity const & ref);
	GameEntity &		operator=(GameEntity const & ref);

};

#endif
