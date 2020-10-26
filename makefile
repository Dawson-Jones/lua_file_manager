version=0.01

name=lua-filemanager
dist=$(name)-$(version)

## Linux/BSD
LDFLAGS += -shared -fPIC -std=c99

LUA_INCLUDE_DIR ?= /usr/local/include/luajit-2.1/
#LUA_INCLUDE_DIR ?= /root/wrk/obj/LuaJIT-2.0.4/src

#CFLAGS ?= -O2 -Wall
CFLAGS ?= -g -O0 -Wall
override CFLAGS += -fpic -I$(LUA_INCLUDE_DIR)

INSTALL ?= install

.PHONY: all clean dist test t

#CC = gcc
RM = rm -f

lua-filemanager.so : interface.o file_remove.o
	$(CC) $(LDFLAGS) -o $@ $^ -lz

interface.o : interface.c
file_remove.o : file_remove.c

.PHONY: clean
clean:
	$(RM) *.so *.o
