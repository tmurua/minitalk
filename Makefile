#Target names
NAME_SERVER = server
NAME_CLIENT = client

#Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

#Directories for helper functions
PRINTFDIR = ./ft_printf
LIBFTDIR = ./ft_printf/libft

#Source and object files for server
SRC_SERVER = server.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)

#Source and object files for client
SRC_CLIENT = client.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

#Generating the compile files (default target)
all: $(NAME_SERVER) $(NAME_CLIENT)

#Server target and dependencies
$(NAME_SERVER): $(OBJ_SERVER)
	make -C $(PRINTFDIR)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(PRINTFDIR)/libftprintf.a $(LIBFTDIR)/libft.a

#Client target and dependencies
$(NAME_CLIENT): $(OBJ_CLIENT)
	make -C $(PRINTFDIR)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(PRINTFDIR)/libftprintf.a $(LIBFTDIR)/libft.a

#Generating object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Clearing out all the .o files
clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	make -C $(PRINTFDIR) clean
	make -C $(LIBFTDIR) clean

#Removing executable files and cleaning dependencies
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make -C $(PRINTFDIR) fclean
	make -C $(LIBFTDIR) fclean

#Rebuild target: cleans all object files, exe, and then builds the project
re: clean all

#Declare phony targets to avoid conflicts with file names
.PHONY: all clean fclean re
