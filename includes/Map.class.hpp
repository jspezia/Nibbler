#ifndef Map_HPP
# define Map_HPP

#include <iostream>

class Map
{

public:

	Map(char *height, char *width);
	~Map();
	int 		getHeight(void) const;
	int 		getWidth(void) const;
	std::string	printHW(void) const;
	Map		&operator=(Map const &rhs);

protected:

	Map(void);


private:

	int 	_height;
	int		_width;

};

std::ostream		&operator<<(std::ostream &o, Map const &i);

#endif
