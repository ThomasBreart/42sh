NAME = 21sh
CC = cc
FLAGS = -Wall -Wextra -Werror -g
LIBFT = lib/libft/

SRC := $(filter %.c, $(shell find src -type f))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "-> Building libft"
	@make -C $(LIBFT)
	@echo "-> Linkin"
	@$(CC) -o $@ $(OBJ) $(FLAGS) $(LIBFT)libft.a -ltermcap
	@echo "-> Perfect !"

%.o: %.c
	@echo "-> Compiling $<"
	@$(CC) $(FLAGS) -I inc/ -o $@ -c $<

clean:
	@echo "Removing obj files"
	@rm -f $(OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@echo "Removing binary"
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

test: $(OBJ) tests/main_tests.o
	@echo "-> Building libft"
	@make -C $(LIBFT)
	@echo "-> Linkin"
	@$(CC) -o $@ $(OBJ) tests/main_tests.o $(FLAGS) $(LIBFT)libft.a -ltermcap
	@echo "-> Perfect !"

.PHONY: all clean fclean re

