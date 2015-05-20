#include <string>
#include <dlfcn.h>
#include <iostream>

void		dlerror_wrapper(void)
{
	std::cerr << "Err: " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	(void)ac;
	(void)av;

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
	return (EXIT_SUCCESS);
}
