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

	if (ac >= 4)
	{
		if (!str_is_digit(av[1]) || !str_is_digit(av[2]))
			handle_error("invalid width or height value", IS_CRITIC);
		else
		{
			width = atoi(av[1]);
			height = atoi(av[2]);
			if (ac == 4)
			{
				dlib_path = av[3];
			}
			if (width < MIN_WIDTH || width > MAX_WIDTH
					|| height < MIN_HEIGHT || height > MAX_HEIGHT)
				handle_error("width or height out of range", IS_CRITIC);
			else
			{
				printf("new Game\n");
				game = new Game(width, height);
				game->init(dlib_path);
				game->loop();
			}
		}
	}
	else
		std::cout << av[0] << " width height [dlib_path]" << std::endl;
	return (EXIT_SUCCESS);
}
