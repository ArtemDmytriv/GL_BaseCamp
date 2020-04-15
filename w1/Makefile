all: server client

server: server.c linux/linxfunc.c
	gcc server.c linux/linxfunc.c -o server -lncurses

client: client.c linux/linxfunc.c
	gcc client.c linux/linxfunc.c -o client -lncurses
