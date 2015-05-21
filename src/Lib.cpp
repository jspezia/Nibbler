#include <locale>
#include <iostream>
#include "Lib.hpp"

bool	str_is_digit(char *str)
{
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	handle_error(std::string msg, bool is_critic)
{
	std::cerr << "Err: " << msg << std::endl;
	if (is_critic)
		exit(EXIT_FAILURE);
}

void	print_message(std::string msg)
{
	std::cout << msg << std::endl;
}
