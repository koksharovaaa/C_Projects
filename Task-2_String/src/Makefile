CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lcheck -lm -lsubunit
FOBJECTS = \
	s21_strstr.o\
	s21_strlen.o\
	s21_strchr.o\
	s21_strpbrk.o\
	s21_strcspn.o\
	s21_to_upper.o\
	s21_to_lower.o\
	s21_insert.o\
	s21_trim.o\
	s21_strerror.o\
	s21_sscanf.o\
	s21_sprintf.o\
	s21_memchr.o\
	s21_memcmp.o\
	s21_memcpy.o\
	s21_memset.o\
	s21_strncat.o\
	s21_strncmp.o\
	s21_strtok.o\
	s21_strncpy.o\
	s21_strrchr.o

all: s21_string.a

test: s21_string_test.o s21_string.a
	@echo "\n---library testing---\n"
	@$(CC) -o test s21_string_test.o $(LIBS) ./s21_string.a
	@./test

s21_string.a: $(FOBJECTS)
	@ar -rcs s21_string.a $(FOBJECTS)
	@ranlib s21_string.a

gcov_report: *.c s21_string.h s21_string_test.h
	@echo "\n---gcov_report creating---\n"
	@$(CC) --coverage -dumpbase '' *.c -o gcov_report_prog $(LIBS)
	@./gcov_report_prog
	@echo "\n---gcov_report results---\n"
	@gcov *.c
	@gcovr -r . --html -o coverage.html

s21_string_test.o: s21_string_test.c s21_string_test.h
	@$(CC) -c $(CFLAGS) s21_string_test.c -o s21_string_test.o

%.o : %.c s21_string.h
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f *.o *.a *.gcno *.gcda *.gcov *.html test gcov_report_prog

rebuild: clean all

clang:
	clang-format -i *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

valgrind:
	make test
	valgrind --tool=memcheck --leak-check=yes ./test
