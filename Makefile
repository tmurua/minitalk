SERVER = server
CLIENT = client

#Declared variables
SERVER_CFILES = server.c
SERVER_OBJECTS = $(SERVER_CFILES:.c=.o)

CLIENT_CFILES = client.c
CLIENT_OBJECTS = $(CLIENT_CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = cc

#Generating the compile files
all: $(SERVER) $(CLIENT)

clean:

fclean: clean

re: clean all
