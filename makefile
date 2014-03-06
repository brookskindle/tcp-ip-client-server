#lab 4 makefile
#cs360
#Brooks Kindle
#Julio DeLeon

CC=gcc
CLIENTEXE=client #name of client executable
SERVEREXE=server #name of server executable
CFLAGS=-m32

debug: CFLAGS += -ggdb
debug: all

all: client server

client: client.c commands.o
	$(CC) client.c commands.o $(CFLAGS) -o $(CLIENTEXE)

server: server.c commands.o 
	$(CC) server.c commands.o $(CFLAGS) -o $(SERVEREXE)

commands.o: commands.h commands.c 
	$(CC) -c commands.c $(CFLAGS)

clean:
	rm -rf *.o $(CLIENTEXE) $(SERVEREXE)
