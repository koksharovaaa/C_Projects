CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror
OBJDIR = ../cat/

all: s21_cat

s21_cat:  s21_cat.h s21_cat.c
	$(CC) $(FLAGS) s21_cat.c -o s21_cat
	
clang:
	clang-format -i *.c *.h
	clang-format -n *.c *.h

rebuild:
	make clean
	make s21_cat

clean:
	rm -rf s21_cat
	
test:
	make clean
	make s21_cat
	bash s21_cat_test.sh