#include "s21_test_matrix.h"

void init_matrix(matrix_t *A, double start, double iteration) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = start;
      start += iteration;
    }
  }
  return;
}
