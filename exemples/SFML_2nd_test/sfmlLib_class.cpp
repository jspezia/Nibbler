# include "sfmlLib_class.hpp"

sfmlLib::sfmlLib(int h, int w, std::string name) :
	_height(h),
	_width(w),
	_name(name)
{
	this->_window = (sf::RenderWindow *)new sf::Window(sf::VideoMode(h, w), name);
}

sfmlLib::~sfmlLib(void)
{}

void			sfmlLib::drawSomething(void) const
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (this->_window->isOpen())
    {

        sf::Event event;
        while (this->_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->_window->close();
        }

        // this->_window->clear();
        // this->_window->draw(shape);
        this->_window->display();
    }

    
    // sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    // while (window.isOpen())
    // {

    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }


}

sfmlLib			*createWindow(const int h, const int w, const std::string &name)
{
	sfmlLib		*newSfml;

	newSfml = new sfmlLib(h, w, name);
	std::cout << "create window" << std::endl;
	return newSfml;
}

void			deleteWindow(sfmlLib *ptr)
{
	delete ptr;
	std::cout << "delete window" << std::endl;
}