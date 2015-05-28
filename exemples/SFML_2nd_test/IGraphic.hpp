#ifndef IGRAPHIC_HPP
# define IGRAPHIC_HPP

#include <iostream>

class IGraphic
{
	public:
		virtual void			drawSomething(void) const = 0;
};

#endif