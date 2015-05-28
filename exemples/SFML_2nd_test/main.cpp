
#include <dlfcn.h>
#include "IGraphic.hpp"

void        dlerror_wrapper(void)
{
    std::cout << "dlerror_wrapper" << std::endl;
    std::cerr << "Error: " << dlerror() << std::endl;
    exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{

    void            *dl_handle;

    dl_handle = dlopen(av[1], RTLD_LAZY | RTLD_LOCAL);
    if (!dl_handle)
        dlerror_wrapper();

    IGraphic            *(*WindowCreator)(int, int, std::string);

    WindowCreator = (IGraphic *(*)(int, int, std::string)) dlsym(dl_handle, "createWindow");
    if (!WindowCreator)
        dlerror_wrapper();

    IGraphic        *newWindow;
    newWindow = WindowCreator(200, 200, "sfml work!");

    newWindow->drawSomething();

    void               (*WindowDestructor)(IGraphic *);
    WindowDestructor = (void(*)(IGraphic*)) dlsym(dl_handle, "deleteWindow");
    if (!WindowDestructor)
        dlerror_wrapper();

    WindowDestructor(newWindow);

    dlclose(dl_handle);

    return 0;
}