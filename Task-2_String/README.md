# s21_string

Собственная реализация стандартной библиотеки string.h на C. При тестировании

## Стек
- C11
- gcc
- check и gcov (unit-тесты)
- Makefile

## Сборка
- make all - собрать s21_string.a
- make test - запустить unit-тесты
- make gcov_report - отчёт о покрытии
- make clean - очистить

## Реализованные функции
- memchr, memcmp, memcpy, memset
- strncat, strchr, strncmp, strncpy, strcspn, strerror, strlen, strpbrk, strrchr, strstr, strtok
- sprintf (частично)
- sscanf (частично)
- to_upper, to_lower, insert, trim