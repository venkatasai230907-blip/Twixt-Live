# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Output executable name
TARGET = twixt

# Object files
OBJS = main.o links.o winning_check.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c links.h winning_check.h
	$(CC) $(CFLAGS) -c $<

links.o: links.c links.h
	$(CC) $(CFLAGS) -c $<

winning_check.o: winning_check.c winning_check.h links.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
