#include <string>
#include <iostream>

extern "C" {

std::string		*test(void)
{
	std::string		*test;

	test = new std::string("hello");
	std::cout << *test << std::endl;
	return test;
}

}
