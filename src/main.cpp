#include <string>
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include "Map.class.hpp"
#include "Snake.class.hpp"
#include "GameEntity.class.hpp"
#include "Time.class.hpp"

void		dlerror_wrapper(void)
{
	std::cerr << "Err: " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
/*
	void			*dl_handle;
	std::string	*	(*test)(void);

	dl_handle = dlopen(av[1], RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle)
		dlerror_wrapper();
	test = (std::string *(*)(void)) dlsym(dl_handle, "test");
	if (!test)
		dlerror_wrapper();
	std::cout << *test() << std::endl;
	dlclose(dl_handle);
*/
	std::cout << "Time.time = " << Time::time << std::endl;
	std::cout << "Time.deltaTime = " << Time::deltaTime << std::endl;
	//std::cout << "Time.currentTime = " << Time::currentTime << std::endl;
	//std::cout << "Time.lastTime = " << Time::lastTime << std::endl;

	while (1) {
		Time::Update();

		std::cout << "Time.time = " << Time::time << std::endl;
		std::cout << "Time.deltaTime = " << Time::deltaTime << std::endl;
		std::cout << "Time.fps = " << Time::fps << std::endl;
		//std::cout << "Time.currentTime = " << Time::currentTime << std::endl;
		//std::cout << "Time.lastTime = " << Time::lastTime << std::endl;

		Time::Sleep(100);
	}

	if (ac >= 3)
	{
		try {
			Map		GE(av[1], av[2]);
		}
		catch (std::exception) {
			std::cout << "height & width e [1 ; 100]" << std::endl;
		}
	}
	else
		std::cout << "./nibbler height width" << std::endl;

	GameEntity		john(1, 2);
	std::cout << john;

	Snake			snake(12, 12);
	std::cout << snake;
	snake.setPosition(14, 18);
	snake.upSpeed(3);
	std::cout << snake;

	return (EXIT_SUCCESS);
}
