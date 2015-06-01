#ifndef LIB_HPP
# define LIB_HPP

# include <string>

# define IS_CRITIC 1
# define TRUE 1
# define FALSE 0

bool	str_is_digit(char *str);

void	handle_error(std::string msg, bool is_critic);
void	print_message(std::string msg);

#endif

