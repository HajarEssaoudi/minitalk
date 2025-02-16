C = gcc
CFLAGS =
NAME_SERVER = server
NAME_CLIENT = client

SRCS_SERVER = server.c
SRCS_CLIENT = client.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

LIB1 = libft/libft.a
LIB2 = ft_printf/libftprintf.a

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(LIB1) $(LIB2) $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIB1) $(LIB2) -o $(NAME_SERVER)

$(NAME_CLIENT): $(LIB1) $(LIB2) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIB1) $(LIB2) -o $(NAME_CLIENT)

$(LIB1):
	make -C libft

$(LIB2):
	make -C ft_printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make -C libft fclean
	make -C ft_printf fclean

do: all clean

re: fclean all

.PHONY: all clean fclean re
