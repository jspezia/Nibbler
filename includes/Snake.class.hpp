#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <iostream>
#include <list>
#include "GameEntity.class.hpp"

class Snake : public GameEntity
{

public:

	Snake(void);
	Snake(int x, int y);
	Snake(Snake const &src);
	~Snake();

	char		getDirection(void) const;
	void		setDirection(char const direction);
	int			getSpeed(void) const;
	void		upSpeed(int const speed);
	int			getLenght(void) const;
	void		upLenght(int const lenght);
	std::string	getState(void) const;
	void		setState(std::string const state);

	void	move(char const direction);

	Snake		&operator=(Snake const &rhs);

protected:


private:
	char			_direction;
	int				_speed;
	int				_lenght;
	std::string		_state;
	std::list<GameEntity>	_body;

};

std::ostream		&operator<<(std::ostream &o, Snake const &i);

#endif
