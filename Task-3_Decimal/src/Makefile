CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lcheck -lm -lsubunit
TEST_SRC = s21_decimal_test.c
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))
FOBJECTS = \
	s21_arithmetic_big.o\
	s21_arithmetic.o\
	s21_comparison.o\
	s21_conversion.o\
	s21_misc_big.o\
	s21_misc_dec.o\
	s21_other.o

all: s21_decimal.a test gcov_report

s21_decimal.a: $(FOBJECTS)
	@ar -rcs s21_decimal.a $(FOBJECTS)
	@ranlib s21_decimal.a

test: $(TEST_OBJ) s21_decimal.a
	@echo "\n---library testing---\n"
	@$(CC) -o test $(TEST_OBJ) $(LIBS) ./s21_decimal.a
	@./test

gcov_report: *.c tests/$(TEST_SRC) s21_decimal.h
	@echo "\n---gcov_report creating---\n"
	@$(CC) --coverage -dumpbase '' *.c tests/$(TEST_SRC) -o gcov_report_prog $(LIBS)
	@./gcov_report_prog
	@echo "\n---gcov_report results---\n"
	@gcov *.c
	@lcov -t "gcov_report_prog" -o test_coverage.info -c -d .
	@genhtml -o report test_coverage.info

gcov_report_2: *.c tests/$(TEST_SRC) s21_decimal.h
	@echo "\n---gcov_report creating---\n"
	@$(CC) --coverage -dumpbase '' *.c tests/$(TEST_SRC) -o gcov_report_prog $(LIBS)
	@./gcov_report_prog
	@echo "\n---gcov_report results---\n"
	@gcov *.c
	@gcovr -r . --html -o coverage.html

$(TEST_OBJ): tests/$(TEST_SRC)
	@$(CC) -c $(CFLAGS) tests/$(TEST_SRC) -o $(TEST_OBJ)

%.o : %.c s21_decimal.h
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f *.o *.a *.gcno *.gcda *.gcov *.html test mini gcov_report_prog

rebuild: clean all

clang:
	clang-format -i *.c *.h
	clang-format -i tests/*.c *.h

ccheck:
	clang-format -n *.c *.h
	clang-format -n tests/*.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test


