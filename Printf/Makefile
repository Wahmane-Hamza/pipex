# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 15:25:42 by hwahmane          #+#    #+#              #
#    Updated: 2024/12/05 16:17:06 by hwahmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c ft_print_char.c ft_print_str.c \
						ft_print_ptr.c \
						ft_print_nbr.c \
						ft_print_unsig_nbr.c \
						ft_print_hexa.c 

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror 
NAME = libftprintf.a
CC = cc
AR = ar rc
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re