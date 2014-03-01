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

client: client.c
	$(CC) client.c $(CFLAGS) -o $(CLIENTEXE)

server: server.c
	$(CC) server.c $(CFLAGS) -o $(SERVEREXE)

clean:
	rm -rf *.o $(CLIENTEXE) $(SERVEREXE)
