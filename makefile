#lab 4 makefile
#cs360
#Brooks Kindle
#Julio DeLeon

CC=gcc
CLIENTEXE=client #name of client executable
SERVEREXE=server #name of server executable
#CFLAGS=-m32

#debug: CFLAGS += -ggdb
debug: all

all: client server

client: client.c commands.o remoteCommands.o localCommands.o
	$(CC) client.c commands.o remoteCommands.o localCommands.o $(CFLAGS) -o $(CLIENTEXE)

server: server.c commands.o remoteCommands.o localCommands.o
	$(CC) server.c $(CFLAGS) -o $(SERVEREXE)

commands.o: commands.h commands.c localCommands.h localCommands.c\
remoteCommands.h remoteCommands.c
	$(CC) -c commands.c remoteCommands.c localCommands.c $(CFLAGS)

clean:
	rm -rf *.o $(CLIENTEXE) $(SERVEREXE)
