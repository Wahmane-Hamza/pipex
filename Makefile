NAME = pipex
BNAME = pipex_bonus

SRCS = pipex.c commands_help.c commands_help2.c check.c
SRCB = pipex_bonus.c commands_help.c commands_help2.c \
		commands_bonus.c check.c\
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCB:.c=.o)

HEADER = -I.
DEPS = pipex.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

bonus: $(BNAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)

$(BNAME): $(OBJSB)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJSB) -Llibft -lft -o $(BNAME)

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(OBJS) $(OBJSB)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME) $(BNAME)

re: fclean all

.PHONY: all clean fclean re
