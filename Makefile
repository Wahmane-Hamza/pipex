NAME = pipex

SRCS = pipex.c commands_help.c commands_help2.c \
		commands_help3.c check.c\
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

HEADER = -I.
DEPS = pipex.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
