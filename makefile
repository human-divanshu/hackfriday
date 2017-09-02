CC=g++
CFLAGS= -std=c++11
DEPS = myfuns.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: myfuns.cpp shell.cpp cmd.cpp cmd2.cpp cmd3.cpp
	$(CC) $(CFLAGS) -o shell myfuns.cpp shell.cpp cmd.cpp cmd2.cpp cmd3.cpp