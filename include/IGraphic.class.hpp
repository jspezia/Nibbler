#ifndef IGRAPHIC_CLASS_HPP
# define IGRAPHIC_CLASS_HPP

# include <array>
# include "GameEntity.class.hpp"

class IGraphic
{
	public:
		virtual ~IGraphic(void) {}

		virtual void		draw(void) = 0;
		virtual int			getInput(void) = 0;
		// virtual void		exit(void) = 0;
};

#endif
