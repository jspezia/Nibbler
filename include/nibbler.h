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
    NORTH = 0, /*    N    */
    EAST  = 1, /*  W + E  */
    SOUTH = 2, /*    S    */
    WEST  = 3  /*         */
};

#endif
