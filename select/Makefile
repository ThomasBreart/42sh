# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/08/11 17:14:40 by fjacquem          #+#    #+#              #
#    Updated: 2015/12/16 00:06:28 by fjacquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		ft_select
FLAGS =		-Wall -Wextra -Werror -g
CC =		gcc
LIBFT =		./libft
LIBFT_LIB =	$(LIBFT)/libft.a

# select
SRC_SELECT = select.c select_2.c select_3.c tool.c
OBJ_SELECT = $(SRC_SELECT:.c=.o)

# explorer
SRC_EXPLORER =	add_fcts.c extension_map.c file.c explorer.c initialize.c\
				ls.c opts.c print.c print_bis.c tools.c file_bis.c
OBJ_EXPLORER =	$(SRC_EXPLORER:.c=.o)

# ...
SRC =	$(addprefix explorer/, $(SRC_EXPLORER))\
		$(addprefix src/, $(SRC_SELECT))
OBJ =	$(OBJ_EXPLORER) $(OBJ_SELECT)

all: $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT) addbonus

$(OBJ):
	$(CC) -I includes -I $(LIBFT) $(FLAGS) -c $(SRC)

$(NAME): $(LIBFT_LIB) $(OBJ)
	$(CC) -I includes -I $(LIBFT) $(FLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) -ltermcap

clean:
	rm -f $(OBJ)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(OBJ) $(NAME)
	make -C $(LIBFT) fclean

re:		fclean all
