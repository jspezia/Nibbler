#ifndef SFML_CLASS_HPP
# define SFML_CLASS_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "IGraphic.class.hpp"

# define MAX_WIDTH		800
# define MAX_HEIGHT		600

/*
**		COLOR
**							|R|, |G|, |B|
*/
# define PINK				217,  36, 105
# define PURPLE				157, 124, 255
# define CYAN				117, 176, 195
# define YELLOW				227, 219, 115
# define ORANGE				228, 126,   0
# define GREEN				177, 227,  54
# define BROWN				115, 111,  79
# define DARK_GREY			 44,  44,  39
# define LIGHT_GREY			142, 143, 137
# define BLACK				  0,   0,   0
# define WHITE				255, 255, 255

class Sfml : public IGraphic {

	public:
		Sfml(int width, int height);
		~Sfml(void);

		void	draw(void);

	private:
		Sfml(void);
		Sfml(Sfml const & ref);
		Sfml &	operator=(Sfml const & ref);

		void		_init(void);
		void		_destroy(void);
		void		_clear(void);
		void		_drawGrid(void);

		int					_x;
		int					_y;

		int					_squareSize;
		int					_winWidth;
		int					_winHeight;
		// sf::Font *			_font;
		sf::RenderWindow *	_win;

};

#endif
