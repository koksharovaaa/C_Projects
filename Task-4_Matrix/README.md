# s21_matrix

Собственная реализация библиотеки для работы с матрицами на C.

## Стек
- C11
- gcc
- check и gcov (unit-тесты)
- Makefile

## Сборка
- make all: собрать s21_matrix.a
- make test: запустить unit-тесты
- make gcov_report: отчёт о покрытии
- make clean: очистить

## Реализованные функции
- create_matrix, remove_matrix: создание и уничтожение матриц в памяти
- eq_matrix: сравнение матриц
- sum_matrix, sub_matrix: сложение и вычитание матриц
- mult_matrix, mult_number: умножение матрицы на матрицу, умножение матрицы на число
- transpose: транспонирование
- determinant: определение определителя
- calc_complements: вычисление матрицы алгебраических дополнений
- inverse_matrix: поиск обратной матрицы