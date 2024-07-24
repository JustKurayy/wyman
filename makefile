PROGRAM = wyman
C_FILES := $(wildcard *.c)
CC = cc
CFLAGS = -Wall -pedantic
LDLIBS = -liw

build: main.c
		$(CC) $(CFLAGS) main.c -o wyman $(LDLIBS)

clean: 
		$(RM) wyman wyman.o
