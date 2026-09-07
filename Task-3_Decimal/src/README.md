# s21_decimal

В этом проекте я реализовала библиотеку s21_decimal.h на языке программирования С. Эта библиотека должна добавить возможность работы с типом «decimal», который отсутствует в стандарте языка. 

## Стек
- C11
- gcc
- check и gcov (unit-тесты)
- Makefile

## Сборка
- make all: собрать s21_decimal.a
- make test: запустить unit-тесты
- make gcov_report: отчёт о покрытии
- make clean: очистить

## Реализовано
- Сложение, вычитание, умножение, деление
- Операторы сравнения
- Конвертация: int to and from decimal, float to and from decimal
- Округление: floor, round, truncate, negate
