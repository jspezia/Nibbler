CC					=	g++ -std=c++11 -Wno-deprecated
NAME				=	nibbler
FLAGS				=	-Werror -Wextra -Wall

INCLUDE				=	./include
SRC					=	DynamicLibHandler.class.cpp						\
						Game.class.cpp									\
						GameEntity.class.cpp							\
						Player.class.cpp								\
						Lib.cpp											\
						Map.class.cpp									\
						Snake.class.cpp									\
						Time.class.cpp									\
						main.cpp
SRCS				=	$(patsubst %, src/%, $(SRC))
OBJS				=	$(SRCS:src/%.cpp=obj/%.obj)

# necessary files for sfml
BREW_INCLUDE		=	~/.brew/include
SFML_LIBS			=	~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system
SFML				=	~/.brew/lib/libsfml-audio*						\
						~/.brew/lib/libsfml-graphics*					\
						~/.brew/lib/libsfml-network*					\
						~/.brew/lib/libsfml-system*						\
						~/.brew/lib/libsfml-window*


# SFML
SFML_NAME			=	libnibbler_sfml.so
SFML_INCLUDE		=	sfml/include
SFML_SRC			=	Sfml.class.cpp
SFML_SRCS			=	$(patsubst %, sfml/src/%, $(SFML_SRC))
SFML_LN				=	sfml/include/SFML

# NCURSES
NCURSES_NAME		=	libnibbler_ncurses.so
NCURSES_LIB			=	-lncurses
NCURSES_INCLUDE		=	ncurses/include
NCURSES_SRC			=	Ncurses.class.cpp
NCURSES_SRCS		=	$(patsubst %, ncurses/src/%, $(NCURSES_SRC))

# GLFW
CMAKE				=	cmake

GLFW_NAME			=	libnibbler_glfw.so
GLFW_LIB_DIR		=	glfw/lib
GLFW_LIB			=	$(GLFW_LIB_DIR)/src/libglfw3.a
GLFW_INCLUDE		=	glfw/include
GLFW_SRC			=	Glfw.class.cpp
GLFW_SRCS			=	$(patsubst %, glfw/src/%, $(GLFW_SRC))
GLFW_LN				=	glfw/include/GLFW

FRAMEWORK			= -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework GLUT
# LDFLAGS				= -L $(GLFW_LIB_DIR)/src -lglfw3 $(FRAMEWORK)
# CFLAGS				= -I $(GLFW_LIB_DIR)/include/GLFW -Wno-deprecated

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: obj $(NAME) $(GLFW_NAME)
# $(SFML_NAME) $(NCURSES_NAME)

$(NAME): $(OBJS)
	@$(CC) -o $@ $^ -I $(INCLUDE)
	@echo "Compiling" [ $@ ] $(SUCCESS)

obj:
	@mkdir -p obj

obj/%.obj: src/%.cpp
	@$(CC) -c -o $@ $< -I $(INCLUDE)
	@echo "Linking" [ $< ] $(OK)

# SFML

$(SFML_NAME): $(SFML) $(SFML_LN) $(SFML_SRCS)
	@$(CC) -o $@ -shared -fPIC -I $(INCLUDE) -I $(SFML_INCLUDE) -L $(SFML_LIBS) $(SFML_SRCS) obj/GameEntity.class.obj obj/Map.class.obj
	@echo "Compiling" [ $@ ] $(SUCCESS)

$(SFML_LN):
	@ln -s ~/.brew/include/SFML sfml/include/SFML

$(SFML):
	brew install sfml


# GLFW

$(GLFW_NAME): $(CMAKE) glfw/lib/CMakeLists.txt $(GLFW_LIB)
	$(CC) -o $@ -shared -fPIC -I $(INCLUDE) -I $(GLFW_INCLUDE) -L $(GLFW_LIB_DIR)/src -lglfw3 $(FRAMEWORK) -I $(GLFW_LIB_DIR)/include/GLFW $(GLFW_SRCS) obj/GameEntity.class.obj obj/Map.class.obj
	@echo "Compiling" [ $@ ] $(SUCCESS)

$(GLFW_LIB):
	cd $(GLFW_LIB_DIR) && \
	$(CMAKE) . && \
	make

$(CMAKE):
	brew update
	brew install cmake

glfw/lib/CMakeLists.txt:
	git submodule init
	git submodule update


# NCURSES

$(NCURSES_NAME): $(NCURSES_SRCS)
	@$(CC) -o $@ -shared -fPIC -I $(INCLUDE) -I $(NCURSES_INCLUDE) $(NCURSES_LIB) $(NCURSES_SRCS) obj/GameEntity.class.obj obj/Map.class.obj

clean:
	@rm -f $(OBJS)
	@rm -rf obj
	@echo "Cleaning" [ $(NAME) ] $(OK)

fclean: clean
	@rm -f $(NAME)
	@echo "Delete" [ $(NAME) ] $(OK)
	@rm -f $(SFML_NAME)
	@echo "Delete" [ $(SFML_NAME) ] $(OK)

update_env:
	sh script.sh

re: fclean all

.PHONY: all clean fclean re update_env
