NAME		=	exec

INCLUDE		=	~/.brew/include
SFML_LIB	=	~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system
SFML		=	~/.brew/lib/libsfml-audio.dylib			\
				~/.brew/lib/libsfml-graphics.dylib		\
				~/.brew/lib/libsfml-network.dylib		\
				~/.brew/lib/libsfml-system.dylib		\
				~/.brew/lib/libsfml-window.dylib

all: $(NAME)

$(NAME): $(SFML)
	export LD_LIBRARY_PATH=$HOME/.brew/lib
	g++ main.cpp -I $(INCLUDE) -L $(SFML_LIB) -o $(NAME)

clean:
	rm -rf $(NAME)

$(SFML):
	brew install sfml

fclean: clean

re: fclean all

.PHONY: all
