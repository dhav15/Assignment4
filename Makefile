# Do not edit the contents of this file.
CC = gcc
CFLAGS = -Werror -Wall -g -std=gnu99
LDFLAGS = -lrt -lpthread
TARGET = Question1 
OBJFILES = Question1.o 
all: $(TARGET)

Question1: a4.c
	$(CC) $(CFLAGS) -o q1 q1.c $(LDFLAGS)


runq1: a4
	./a4 10 5 7 8

clean:
	rm -f $(OBJFILES) $(TARGET) *~ 
