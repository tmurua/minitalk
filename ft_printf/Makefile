NAME = libftprintf.a
LIBFTNAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFTDIR = ./libft

#Declared variables
CFILES =	ft_print_char.c			ft_print_str.c	ft_print_int.c		\
			ft_print_unsigned_int.c	ft_print_hex.c	ft_print_pointer.c	\
			ft_printf.c

OBJECTS = $(CFILES:.c=.o)

#Generating the compile files
$(NAME): $(OBJECTS)
	make -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFTNAME) .
	mv $(LIBFTNAME) $(NAME)
	ar -rcs $(NAME) $(OBJECTS)

all: $(NAME)

#Generating object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< $^

#Clearing out all the .o files
clean:
	rm -rf $(NAME) $(OBJECTS)
	cd $(LIBFTDIR) && make clean

fclean: clean
	rm -rf $(NAME)
	cd $(LIBFTDIR) && make fclean

re: clean all
