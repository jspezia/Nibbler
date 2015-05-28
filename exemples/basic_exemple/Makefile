NAME		=	test

CC			=	g++

SRC			=	main.cpp

LIB_C		=	square.c
LIBC_SO		= $(patsubst %.c, lib%c.so, $(LIB_C))

LIB_CPP		=	square.cpp
LIBCPP_SO		= $(patsubst %.cpp, lib%cpp.so, $(LIB_CPP))

FLAGS_LIB	=	-shared -fPIC

all: $(NAME)

$(NAME): $(LIBC_SO) $(LIBCPP_SO)
	@$(CC) -o $(NAME) $(SRC)

$(LIBC_SO):
	gcc $(FLAGS_LIB) -o $(LIBC_SO) $(LIB_C)

$(LIBCPP_SO):
	g++ $(FLAGS_LIB) -o $(LIBCPP_SO) $(LIB_CPP)


clean:
	rm -rf $(LIBC_SO)
	rm -rf $(LIBCPP_SO)

fclean: clean
	rm -rf $(NAME)

re: fclean all

run:
	./$(NAME) $(LIBC_SO)
	./$(NAME) $(LIBCPP_SO)

.PHONY: all clean fclean re run
