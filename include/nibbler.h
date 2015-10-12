#ifndef NIBBLER_H
# define NIBBLER_H

# define DLIB_PATH(X)   "libnibbler_" X ".so"
# define DLIB_NCURSES   DLIB_PATH("ncurses")
# define DLIB_SFML      DLIB_PATH("sfml")
# define DLIB_GLFW      DLIB_PATH("glfw")

# define DLIB_DEFAULT   DLIB_GLFW

enum        e_dlib
{
    NCURSES,
    SFML,
    GLFW
};

enum        e_direction
{
    NORTH = -2,
    WEST  = -1,
    EAST  =  1,
    SOUTH =  2
};

#endif
