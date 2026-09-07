CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror

all: s21_grep

s21_grep:  s21_grep.h s21_grep.c
	$(CC) $(FLAGS) s21_grep.c -o s21_grep
	
clang:
	clang-format -i *.c *.h
	clang-format -n *.c *.h

rebuild:
	make clean
	make s21_grep

clean:
	rm -rf s21_grep
	
test:
	make clean
	make s21_grep
	bash s21_grep_test.sh