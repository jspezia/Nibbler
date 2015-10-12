#ifndef IGRAPHIC_CLASS_HPP
# define IGRAPHIC_CLASS_HPP

# include <array>
# include "GameEntity.class.hpp"
# include "Map.class.hpp"

class IGraphic
{
	public:
		virtual ~IGraphic(void) {}

        virtual void        init(void) = 0;
        virtual void        draw(Map *map) = 0;
        virtual int         getInput(void) = 0;
        virtual void        close(void) = 0;
};

#endif
