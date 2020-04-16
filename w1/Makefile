CC=gcc

ifeq ($(OS), Windows_NT)
	LIBS=-lws2_32
	INCL=win/winfunc.c
else
	LIBS=-lX11
	INCL=linux/linxfunc.c
endif

.PHONY: all test

all: server client

server: server.c $(INCL)
		$(CC) server.c $(INCL) -o server $(LIBS)

client: client.c $(INCL)
		$(CC) client.c $(INCL) -o client $(LIBS)

test:
	(info ****TEST****)



