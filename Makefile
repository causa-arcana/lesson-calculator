CFLAGS = -Wall -Wextra

SRCS = ast.c interpreter.c lexer.c token.c
SRC_OBJS = $(addsuffix .o, $(addprefix src/, $(SRCS)))

EXES = calc
EXE_BINS = $(EXES)
EXE_OBJS = $(addsuffix .c.o, $(addprefix exe/, $(EXES)))

TESTS = ast interpreter lexer_from_example_foo lexer_from_str_foo lexer_two_plus_two_mul_two object
TEST_BINS = $(addprefix tests/, $(TESTS))
TEST_OBJS = $(addsuffix .c.o, $(TEST_BINS))

.PHONY: all clean test test_ast test_interpreter test_lexer_from_example_foo test_lexer_from_str_foo test_lexer_two_plus_two_mul_two test_object

all: $(EXES)

clean:
	rm -f $(SRC_OBJS) $(EXE_BINS) $(EXE_OBJS) $(TEST_BINS) $(TEST_OBJS)

test: $(addprefix test_, $(TESTS))

%.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

calc: exe/calc.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

tests/ast: tests/ast.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

tests/interpreter: tests/interpreter.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

tests/lexer_from_example_foo: tests/lexer_from_example_foo.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

tests/lexer_from_str_foo: tests/lexer_from_str_foo.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

tests/lexer_two_plus_two_mul_two: tests/lexer_two_plus_two_mul_two.c.o $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

tests/object: tests/object.c.o $(SRC_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test_ast: tests/ast
	$^

test_interpreter: tests/interpreter
	$^

test_lexer_from_example_foo: tests/lexer_from_example_foo
	$^

test_lexer_from_str_foo: tests/lexer_from_str_foo
	$^

test_lexer_two_plus_two_mul_two: tests/lexer_two_plus_two_mul_two
	$^

test_object: tests/object
	$^
