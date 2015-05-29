NAME		=	a.out
CC			=	g++
FLAGS		=	-Werror -Wextra -Wall

# necessary files for sfml
BREW_INCLUDE		=	~/.brew/include
SFML_LIB			=	~/.brew/lib -lsfml-graphics.2.2.0 -lsfml-window.2.2.0 -lsfml-system.2.2.0
SFML				=	~/.brew/lib/libsfml-audio.2.2.0.dylib			\
						~/.brew/lib/libsfml-graphics.2.2.0.dylib		\
						~/.brew/lib/libsfml-network.2.2.0.dylib			\
						~/.brew/lib/libsfml-system.2.2.0.dylib			\
						~/.brew/lib/libsfml-window.2.2.0.dylib

# all .cpp for exec
SRC					=	DynamicLibHandler.class.cpp	\
						Game.class.cpp				\
						GameEntity.class.cpp		\
						Lib.cpp						\
						Map.class.cpp				\
						Snake.class.cpp				\
						Time.class.cpp				\
						main.cpp

INCLUDE				=	./includes
SRCS				=	$(patsubst %, src/%, $(SRC))
#OBJS				=	$(SRC:%.cpp=obj/%.o)

# all .cpp for compile sfml library
#SFML_CPP			=	sfml.class.cpp
#SFML_SRC			= $(patsubst %, src/%, $(SFML_CPP))

#LIBSFML_SO			=	libsfml.so

all: obj $(NAME)
$(NAME): $(SFML) $(OBJS)
	$(CC) $(SRCS) -I $(INCLUDE) -o $(NAME)

obj:
	mkdir -p obj

$(SFML):
	brew install sfml

update_env:
	@echo "Please use the next command:		export LD_LIBRARY_PATH=~/.brew/lib"

$(LIBSFML_SO):
	g++ -shared -fPIC -I $(BREW_INCLUDE) -I $(INCLUDE) -L $(SFML_LIB) -o $(LIBSFML_SO) $(SFML_SRC)

clean:
	rm -rf $(LIBSFML_SO))
	rm -rf obj/*

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re update_env
