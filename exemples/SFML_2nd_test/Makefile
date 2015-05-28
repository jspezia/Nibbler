NAME		=	a.out

INCLUDE		=	~/.brew/include
SFML_LIB	=	~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system
SFML		=	~/.brew/lib/libsfml-audio.dylib			\
				~/.brew/lib/libsfml-graphics.dylib		\
				~/.brew/lib/libsfml-network.dylib		\
				~/.brew/lib/libsfml-system.dylib		\
				~/.brew/lib/libsfml-window.dylib

SRC			=	sfmlLib_class.cpp

LIB_GRAHIC	=	libsfml.so

all: $(NAME)

$(NAME): $(SFML) $(LIB_GRAHIC)
	g++ main.cpp -o $(NAME)

$(SFML):
	brew install sfml

update_env:
	export LD_LIBRARY_PATH=$HOME/.brew/lib

$(LIB_GRAHIC):
	g++ -shared -fPIC -I $(INCLUDE) -L $(SFML_LIB) -o $(LIB_GRAHIC) $(SRC)

clean:
	rm -rf $(LIB_GRAHIC)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re update_env
