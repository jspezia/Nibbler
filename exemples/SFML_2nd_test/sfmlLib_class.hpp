
#ifndef SFMLLIB_CLASS_HPP
# define SFMLLIB_CLASS_HPP

# include "IGraphic.hpp"
# include <SFML/Graphics.hpp>
# include <iostream>

class sfmlLib : public IGraphic
{
	private:
		std::string			_name;
		int					_height;
		int					_width;
		sf::RenderWindow	*_window;
		sfmlLib(void);

	public:
		sfmlLib(int h, int w, std::string name);

		~sfmlLib(void);

		void		drawSomething(void) const;
};

extern "C"
{
	sfmlLib		*createWindow(const int h, const int w, const std::string &name);
	void		deleteWindow(sfmlLib *ptr);
}

#endif