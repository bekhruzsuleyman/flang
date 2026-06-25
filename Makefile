CC := gcc
SRC := $(wildcard src/*.c)

CFLAGS := -g -fsanitize=address -Wall -Wextra

all: clean flang

flang: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o flang

clean:
	rm -f flang

.PHONY: all clean