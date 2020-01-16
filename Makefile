# Makefile for ex1-q1 
CFLAGS = -Wall
LDFLAGS = -lm # not really needed for this exercise
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
OS := $(shell uname)
ifneq (,$(findstring CYGWIN_NT,$(OS)))
EXT = .exe
else
EXT =
endif

PROG = ex1_q1$(EXT)

all: $(PROG) test
 
ex1_q1.o: ex1_q1.c ex1_q1.h
	$(CC) $(CFLAGS) -c ex1_q1.c
		  
$(PROG): ex1_q1.o
	$(CC) $(CFLAGS) ex1_q1.o -o ex1_q1

clean:
	rm -vf *.o $(PROG) *.log

test:
	./$(PROG) < in.txt > out.log