SRCSDIR	= srcs
INCDIR	= includes
SRCS	= pipex.c utils.c utils2.c error.c
OBJS	= $(addprefix $(SRCSDIR)/, $(SRCS:.c=.o))
LIBDIR	= libft
LIB		= libft.a
NAME	= pipex
CC		= cc
CFLAG	= -Wall -Wextra -Werror -fsanitize=address

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
