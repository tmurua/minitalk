NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

PRINTFDIR = ./ft_printf
LIBFTDIR = ./ft_printf/libft

SRC_SERVER = server.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)

SRC_CLIENT = client.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

#Generating the compile files
all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	make -C $(PRINTFDIR)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(PRINTFDIR)/libftprintf.a $(LIBFTDIR)/libft.a

$(NAME_CLIENT): $(OBJ_CLIENT)
	make -C $(PRINTFDIR)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(PRINTFDIR)/libftprintf.a $(LIBFTDIR)/libft.a

#Generating object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Clearing out all the .o files
clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	make -C $(PRINTFDIR) clean
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make -C $(PRINTFDIR) fclean
	make -C $(LIBFTDIR) fclean

re: clean all

.PHONY: all clean fclean re
