CC = gcc
CFLAGS = -g -DDEBUG_TRACE_EXECUTION

.PHONY: clean clean_run

SRCS := $(shell find . -name '*.c')

SRC := $(SRCS:.c=.o)

$(SRC): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clox: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o clox

run: clox
	./clox

clean_run: | clean clox run

clean:
	rm -rf *.o clox

