# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 01:10:57 by ochouikh          #+#    #+#              #
#    Updated: 2023/05/05 20:24:43 by ochouikh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = manda/main.c \
	manda/utils.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(LIBFT_OBJ) $(OBJ)
	cc $(FLAGS) -g $(LIBFT) $(OBJ) -o $(NAME)

manda/%.o: manda/%.c manda/philo.h
	cc $(FLAGS) -g -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
