CFLAGS = -Wall -Wextra

SRCS = lexer.c token.c
SRC_OBJS = $(addsuffix .o, $(addprefix src/, $(SRCS)))

EXES = calc
EXE_BINS = $(EXES)
EXE_OBJS = $(addsuffix .c.o, $(addprefix exe/, $(EXES)))

TESTS = lexer_from_example_foo lexer_from_str_foo
TEST_BINS = $(addprefix tests/, $(TESTS))
TEST_OBJS = $(addsuffix .c.o, $(TEST_BINS))

.PHONY: all clean test test_lexer_from_example_foo test_lexer_from_str_foo

all: $(EXES)

clean:
	rm -f $(SRC_OBJS) $(EXE_BINS) $(EXE_OBJS) $(TEST_BINS) $(TEST_OBJS)

test: $(addprefix test_, $(TESTS))

%.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

calc: exe/calc.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

tests/lexer_from_example_foo: tests/lexer_from_example_foo.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

tests/lexer_from_str_foo: tests/lexer_from_str_foo.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test_lexer_from_example_foo: tests/lexer_from_example_foo
	$^

test_lexer_from_str_foo: tests/lexer_from_str_foo
	$^
