# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 16:49:05 by ochouikh          #+#    #+#              #
#    Updated: 2023/05/12 17:47:41 by ochouikh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = philo_bonus.c \
	routine_bonus.c \
	philo_infos.c \
	utils_bonus_1.c \
	utils_bonus_2.c \
	ft_itoa.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(LIBFT_OBJ) $(OBJ)
	cc $(FLAGS) $(LIBFT) $(OBJ) -o $(NAME)

%.o: %.c philo_bonus.h
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
