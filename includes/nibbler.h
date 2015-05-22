#ifndef NIBBLER_H
# define NIBBLER_H

/*
	libnibbler_sdl2.so
	libnibbler_sfml.so
	libnibbler_glfw.so
*/

# define DLIB_PATH(X)	"./dll/libnibller_" X ".so"

enum e_direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

#endif
