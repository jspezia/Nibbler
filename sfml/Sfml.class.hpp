#ifndef SFML_CLASS_HPP
# define SFML_CLASS_HPP

# include <array>
# include <IGraphic.class.hpp>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

# define MAX_WIDTH		800
# define MAX_HEIGHT		600

class Sfml : public IGraphic {

	public:
		Sfml(int width, int height);
		~Sfml(void);

		void	draw(void);

	private:
		Sfml(void);
		Sfml(Sfml const & ref);
		Sfml &	operator=(Sfml const & ref);

		_init(void);
		_destroy(void);
		_clear(void);
		_drawGrid(void);

		int					_x;
		int					_y;

		int					_squareSize;
		int					_winWidth;
		int					_winHeight;
		// sf::Font *			_font;
		sf::RenderWindow *	_win;

};

#endif
