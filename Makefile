CFLAGS = -Wall -Wextra

SRCS = lexer.c token.c
SRC_OBJS = $(addsuffix .o, $(addprefix src/, $(SRCS)))

CALC_BIN = calc
CALC_OBJS = src/main.c.o

TESTS = lexer
TEST_BINS = $(addprefix tests/, $(TESTS))
TEST_OBJS = $(addsuffix .c.o, $(TEST_BINS))

.PHONY: all clean test test_lexer

all: calc

clean:
	rm -f $(SRC_OBJS) $(CALC_BIN) $(CALC_OBJS) $(TEST_BINS) $(TEST_OBJS)

test: $(addprefix test_, $(TESTS))

$(CALC_BIN): src/main.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

tests/lexer: tests/lexer.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test_lexer: tests/lexer
	$^
