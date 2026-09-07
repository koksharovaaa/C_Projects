# Simple Bash Utils: Cat, Grep

Собственные реализации утилит cat и grep на C.

## Стек
- C11
- gcc
- regex / pcre2
- Makefile

## Структура
- cat: s21_cat
- grep: s21_grep

## Сборка
cd cat && make s21_cat
cd grep && make s21_grep

## Поддержка флагов

### s21_cat
- -b, -e, -n, -s, -t, -v (GNU-версии)
- --number, --squeeze-blank, --number-nonblank

### s21_grep
- -e, -i, -v, -c, -l, -n
- -h, -s, -f, -o
- Парные комбинации: -iv, -in и др.