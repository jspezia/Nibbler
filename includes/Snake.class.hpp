#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <iostream>
#include "GameEntity.class.hpp"

class Snake : public GameEntity
{

public:

	Snake(void);
	Snake(int x, int y);
	Snake(Snake const &src);
	~Snake();

	void	setPosition(int const x, int const y);
	int		getSpeed(void) const;
	void	upSpeed(int const speed);

	Snake		&operator=(Snake const &rhs);

protected:


private:
	int		_speed;

};

std::ostream		&operator<<(std::ostream &o, Snake const &i);

#endif
