#include <string>
#include <iostream>
#include "Lib.hpp"
#include "Game.class.hpp"

int			main(int ac, char *av[])
{
	Game			*game;
	int				width;
	int				height;
	std::string		dlib_path;

	if (ac >= 3)
	{
		if (!str_is_digit(av[1]) || !str_is_digit(av[2]))
			handle_error("invalid width or height value", IS_CRITIC);
		else
		{
			width = atoi(av[1]);
			height = atoi(av[2]);
			/* load dl if passed as argv */
			if (ac == 4)
			{
				dlib_path = av[3];
				// try load..
			}
			if (width < MIN_WIDTH || width > MAX_WIDTH
					|| height < MIN_HEIGHT || height > MAX_HEIGHT)
				handle_error("width or height out of range", IS_CRITIC);
			else
			{
				game = new Game(width, height);
				printf("\n Game loop. \n\n");
				game->loop();
			}
		}
	}
	else
		std::cout << av[0] << " width height [dlib path]" << std::endl;
	return (EXIT_SUCCESS);
}
