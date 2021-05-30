CFLAGS = -Wall -Wextra

OBJS = main.c.o lexer.c.o

.PHONY: clean

calc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f calc $(OBJS)

%.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
