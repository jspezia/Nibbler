#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <iostream>
#include <list>
#include "GameEntity.class.hpp"

class Snake
{

public:
	Snake(int x, int y);
	~Snake();

	int			getDirection(void) const;
	int			getSpeed(void) const;
	int			getLength(void) const;
	std::string	getState(void) const;

	void		setDirection(int const direction);
	void		setState(std::string const state);

	void		upSpeed(int const speed);
	void		upLength(int const length);

	void		init(int x, int y);
	void		move(int const direction);

	GameEntity *				_head;
	std::list<GameEntity *>		_body; //
protected:


private:
	Snake(void);
	Snake(Snake const &src);
	Snake &		operator=(Snake const &rhs);

	int							_direction;
	int							_speed;
	int							_length;
	std::string					_state;
};

std::ostream		&operator<<(std::ostream &o, Snake const &i);

#endif
