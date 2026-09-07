CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
LIBS = -lcheck -lm -lsubunit

LIB_A = s21_matrix.a
LIB_H = $(LIB_A:.a=.h)
LIB_SRC = $(wildcard *.c)
LIB_OBJ = $(LIB_SRC:.c=.o)

TEST_H = tests/s21_test_matrix.h
TEST_SRC = $(wildcard tests/*.c)

all: s21_matrix.a

s21_matrix.a: $(LIB_OBJ)
	@ar rcs $@ $^
	@ranlib $@

$(LIB_OBJ): %.o: %.c $(LIB_H)
	@$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_SRC) $(TEST_H) $(LIB_A)
	@$(CC) $(CFLAGS) -Itests $(TEST_SRC) $(LIB_A) $(LIBS) -o $@
	@rm -f *.o
	@./test

gcov_report: *.c $(TEST_SRC) s21_matrix.h
	@echo "\n---gcov_report creating---\n"
	@$(CC) --coverage -dumpbase '' *.c $(TEST_SRC) -o gcov_report_prog $(LIBS)
	@./gcov_report_prog
	@echo "\n---gcov_report results---\n"
	@gcov *.c
	@gcovr -r . --html-details --gcov-exclude '.*_test_.*' --html -o coverage.html

clean:
	@rm -f *.o *.a *.gcno *.gcda *.gcov *.html *.info *.css test gcov_report_prog
	@rm -rf report


rebuild: clean all

# Clang, cppcheck, valgrind tests
f:
	clang-format -i *.c *.h
	clang-format -i tests/*.c *.h

clang:
	clang-format -n *.c *.h
	clang-format -n tests/*.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test
	