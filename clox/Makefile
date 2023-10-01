CC = gcc
CFLAGS = -g

SRCS := $(shell find . -name '*.c')

SRC := $(SRCS:.c=.o)

$(SRC): $(SRCS)
	$(CC) -c $(SRCS)

clox: $(SRC)
	$(CC) $(SRC) -o clox

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf clox 

