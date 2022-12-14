CC = gcc
FLAGS = -O2
SRC = $(wildcard *.c)
OUT = $(SRC:.c=)

all: $(OUT)

%: %.c
	$(CC) $< $(FLAGS) -o $@

clean:
	rm -f $(OUT)
