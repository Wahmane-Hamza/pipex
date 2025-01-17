NAME = pipex
BNAME = pipex_bonus

SRCS = pipex.c commands_help.c commands_help2.c
SRCB = pipex_bonus.c commands_help.c commands_help2.c

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCB:.c=.o)

HEADER = -I.
DEPS = pipex.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

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
	@rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: all clean fclean re