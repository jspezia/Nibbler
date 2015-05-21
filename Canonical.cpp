#include <string>
#include <fstream>
#include <iostream>

void hppCanon(std::string name, std::string ext)
{
	std::string		file;

	file = name + ext + ".hpp";
	std::ofstream ofs(file.c_str());

	std::string header = "";
	for (unsigned int i = 0; i < name.size(); i++)
	{
		char c = toupper(name[i]);
		header.push_back(c);
	}
	header += "_HPP";

	ofs << "#ifndef " << header << std::endl
		<< "# define " << header << std::endl << std::endl
		<< "#include <iostream>" << std::endl << std::endl
		<< "class " << name << std::endl << "{" << std::endl << std::endl
		<< "public:" << std::endl << std::endl
		<< "	" << name << "(void);" << std::endl
		<< "	" << name << "(" << name << " const &src);" << std::endl
		<< "	~" << name << "();" << std::endl
		<< "	int getVal(void) const;" << std::endl << std::endl
		<< "	" << name << "		&operator=(" << name << " const &rhs);" << std::endl << std::endl
		<< "private:" << std::endl << std::endl
		<< "	int _val;" << std::endl
		<< std::endl << "};" << std::endl << std::endl
		<< "std::ostream		&operator<<(std::ostream &o, " << name << " const &i);"
		<< std::endl << std::endl << "#endif" << std::endl;
	ofs.close();
}

void cppCanon(std::string name, std::string ext)
{
	std::string		file;

	file = name + ext + ".cpp";
	std::ofstream ofs(file.c_str());

	ofs << "#include \"" << name << ext << ".hpp\"" << std::endl << std::endl
		<< name << "::" << name << "(void)" << std::endl << "{" << std::endl
		<< "	return;"
		<< std::endl << "}" << std::endl << std::endl
		<< name << "::" << name << "(" << name << " const &src)" << std::endl
		<< "{" << std::endl
		<< "	*this = src;" << std::endl << "}" << std::endl << std::endl
		<< name << "::~" << name << "(void)" << std::endl << "{" << std::endl
		<< "	return;" << std::endl << "}" << std::endl << std::endl
		<< "int " << name << "::getVal(void) const" << std::endl
		<< "{" << std::endl
		<< "	return this->_val;" << std::endl << "}" << std::endl << std::endl
		<< name << "		&" << name << "::operator=(" << name << " const &rhs)"
		<< std::endl << "{" << std::endl
		<< "	if (this != &rhs)" << std::endl
		<< "		this->_val = rhs.getVal();" << std::endl
		<< "	return *this;" << std::endl << "}" << std::endl << std::endl
		<< "std::ostream		&operator<<(std::ostream &o, " << name
		<< " const &i)" << std::endl << "{"
		<< std::endl << "	o << i.getVal() << std::endl;" << std::endl
		<< "	return o;" << std::endl << "}" << std::endl << std::endl;
	ofs.close();
}

int main(int ac, char **av)
{
	if (ac > 1 && ac < 4)
	{
		std::string ext = ".class";
		if (ac == 3)
			ext = av[2];

		hppCanon(av[1], ext);
		cppCanon(av[1], ext);
	}
	else
		std::cout << "usage: " << av[0] << " <ClassName> [<extName>]" << std::endl;
	return 0;
}
