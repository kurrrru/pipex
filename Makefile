SRCSDIR	= srcs
INCDIR	= includes
SRCS	= main.c pipex.c exec.c rm_quote.c error.c ft_split_pipex.c shebang.c add_shebang.c free_2d.c
GNLDIR	= gnl
GNL		= get_next_line.c get_next_line_utils.c
OBJS	= $(addprefix $(SRCSDIR)/, $(SRCS:.c=.o)) $(addprefix $(GNLDIR)/, $(GNL:.c=.o))
LIBDIR	= libft
LIB		= libft.a
NAME	= pipex
CC		= cc
CFLAG	= -Wall -Wextra -Werror

.DEFAULT_GOAL := all

$(NAME): $(OBJS) $(LIBDIR)/$(LIB)
	$(CC) $(CFLAG) -I $(INCDIR) $(OBJS) $(LIBDIR)/$(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

$(LIBDIR)/$(LIB):
	make -C $(LIBDIR)

clean:
	rm -f $(OBJS) $(LIBDIR)/*.o $(LIBDIR)/*.a

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re
