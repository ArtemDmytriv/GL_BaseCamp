Compile options:
Sorry for missing makefile, i have had difficulties for creating its with Cmake in Windows. (I would greatly appreciate your help in this)

At that moment, works in Windows with GCC compiler (Mingw or Cygwin)

For making server:
gcc server.c winfunc.c -o server -lws2_32

For making client:
gcc client.c winfunc.c -o client -lws2_32

Version specs:

-Now writing data by server to file is missing
-Testing only in local areas