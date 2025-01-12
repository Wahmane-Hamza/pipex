PROG = pipex
SRCS = pipex.c
OBJS = $(SRCS:.c=.o)
HEADER = -I.
DEPS = pipex.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(PROG)

$(PROG): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(PROG)

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(PROG)

re: fclean all

.PHONY: all clean fclean re