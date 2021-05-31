CFLAGS = -Wall -Wextra

SRC_OBJS = main.c.o lexer.c.o token.c.o
OBJS = $(addprefix src/, $(SRC_OBJS))

.PHONY: clean

calc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f calc $(OBJS)

%.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
