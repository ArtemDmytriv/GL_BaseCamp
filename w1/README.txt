Compile options:
Sorry for missing makefile, i have had difficulties for creating its with Cmake in Windows. (I would greatly appreciate your help in this)

At that moment, works in Windows with GCC compiler (Mingw or Cygwin)

For making Windows server:
gcc server.c winfunc.c -o server -lws2_32

For making Windows client:
gcc client.c winfunc.c -o client -lws2_32
**you can add -mwindows flag for spy startup** Please check LOOPCOUNTER in head.h (must be lower 100)

For making Linux server:
make server

For making Linux client:
make client

Version specs:

-Add write data in file by server
-Was testing with linux server and windows client, all is ok
-Was testing with windows server and windows client, all is ok

-Not implemented linux client ver., I will try use for this X11lib
-Have some troubles when clicks in running client window (if clien window minimize/hide all is ok)