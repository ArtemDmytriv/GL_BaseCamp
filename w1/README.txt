Compile options:
Check top defines in file head.h (LOOPCOUNT for count of client request)
Works in Windows with GCC compiler (Mingw or Cygwin)
For working in Linux, you must install x11lib (sudo apt install libx11-dev) in "make test used gnome-terminal (can change in makefile)"

For cross-platform making use command:
make

For cross-platform cleaning use command:
make clean

For cross-platform testing (start server in new prompt and start client) use command:
make test


Version specs:

+Add makefile
+Add write data in file by server (in folder data)
+Was testing with linux server and windows client, all is ok
+Was testing with windows server and windows client, all is ok

+Linux ver. used x11lib for getting current mouse position
-Not implemented mouse clicks
-Have some troubles when clicks in running client window (if clien window minimize/hide all is ok)