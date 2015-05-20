#include <string>
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include "game_entity.class.hpp"

void		dlerror_wrapper(void)
{
	std::cerr << "Err: " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	(void)ac;
	(void)av;

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


	if (ac >= 3)
	{
		try {
			game_entity(av[1], av[2]);
		}
		catch (std::exception) {
			std::cout << "height & width e [1 ; 100]" << std::endl;
		}
	}
	else
		std::cout << "./nibbler height width" << std::endl;

	return (EXIT_SUCCESS);
}

















