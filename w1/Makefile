CC=gcc

ifeq ($(OS), Windows_NT)
	LIBS=-lws2_32
	INCL=win/winfunc.c
else
	LIBS=-lX11
	INCL=linux/linxfunc.c
endif

.PHONY: all test clean

all: server client

server: server.c $(INCL)
		$(CC) server.c $(INCL) -g -o server $(LIBS)

client: client.c $(INCL)
		$(CC) client.c $(INCL) -g -o client $(LIBS)

test:
ifeq ($(OS), Windows_NT)
		cmd /c start cmd /k .\server.exe
		.\client
else
		term
endif 

clean:
ifeq ($(OS), Windows_NT)
		del client.exe server.exe
else
		rm client server
endif 


