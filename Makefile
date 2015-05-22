CC		= g++ -std=c++11
CPATH	= src
OPATH	= obj
HPATH	= includes
FLAGS	= #-Wall -Werror -Wextra

NAME	= nibbler

SRC		= main.cpp								\
		  Game.class.cpp						\
		  Map.class.cpp							\
		  GameEntity.class.cpp					\
		  Player.class.cpp						\
		  Snake.class.cpp						\
		  Time.class.cpp						\
		  DynamicLibHandler.class.cpp			\
		  Lib.cpp

CFILE	= $(patsubst %, $(CPATH)/%, $(SRC))
OFILE	= $(patsubst %.cpp, $(OPATH)/%.o, $(SRC))

# COLORS
C_NO	= "\033[00m"
C_GOOD	= "\033[32m"

all: $(NAME)

$(NAME): $(OPATH) $(OFILE)
	@$(CC) $(FLAGS) $(OFILE) -I $(HPATH) -o $(NAME)
	@echo $(C_GOOD)Creation Executable$(C_NO)

$(OPATH):
	@echo "Creation of building directory"
	@mkdir $(OPATH)

$(OPATH)/%.o: $(CPATH)/%.cpp
	@echo "Creating file $@"
	@$(CC) $(FLAGS) -o $@ -c $^ -I $(HPATH)

clean:
	@echo "Deletion of building directory"
	@rm -rf $(OPATH)

fclean: clean
	@echo "Deletion of $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
