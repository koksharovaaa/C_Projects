#include "s21_matrix.h"

// Additional functions

#define SWAP -1
#define NO_SWAP 1
#define SWAP_ERR 0

int is_matrix_valid(const matrix_t *A) {
  int state = OK;
  if (!A) {
    state = INCORRECT_MATRIX;
  } else if (A->rows < 1 || A->columns < 1) {
    state = INCORRECT_MATRIX;
  }
  return !state;
}

void copy_matrix(const matrix_t *A, matrix_t *B) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      B->matrix[i][j] = A->matrix[i][j];
    }
  }
}

int mult_num(const matrix_t *A, double number, matrix_t *result) {
  int return_value = OK;
  for (int i = 0; i < A->rows && !return_value; i++) {
    for (int j = 0; j < A->columns && !return_value; j++) {
      result->matrix[i][j] = number * A->matrix[i][j];
      if (!isfinite(result->matrix[i][j])) return_value = CALC_ERROR;
    }
  }
  return return_value;
}

int mult_mat(const matrix_t *A, const matrix_t *B, matrix_t *result) {
  int return_value = OK;
  for (int i = 0; i < A->rows && !return_value; i++) {
    for (int j = 0; j < B->columns && !return_value; j++) {
      for (int k = 0; k < A->columns && !return_value; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        if (!isfinite(result->matrix[i][j])) return_value = CALC_ERROR;
      }
    }
  }
  return return_value;
}

void transpose(const matrix_t *A, matrix_t *result) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return;
}

int biggest_to_row(matrix_t *A, int pivot) {
  int return_value = SWAP_ERR;
  int index = pivot;
  for (int i = pivot; i < A->rows; i++) {
    if (!return_value && A->matrix[i][pivot]) {
      return_value = NO_SWAP;
    }
    if (fabs(A->matrix[i][pivot]) - fabs(A->matrix[index][pivot]) > EQ_LIMIT) {
      index = i;
    }
  }

  if (index != pivot) {
    for (int i = 0; i < A->columns; i++) {
      double tmp = A->matrix[pivot][i];
      A->matrix[pivot][i] = A->matrix[index][i];
      A->matrix[index][i] = tmp;
    }
    return_value = SWAP;
  }
  return return_value;
}

double gauss(matrix_t *A) {
  double determinant = 1.0f;
  int swap = 1;
  for (int i = 0; i < A->columns; i++) {
    swap *= biggest_to_row(A, i);
    for (int j = i + 1; j < A->rows && swap; j++) {
      double mult = A->matrix[j][i] / A->matrix[i][i];
      for (int k = i; k < A->columns; k++) {
        A->matrix[j][k] -= A->matrix[i][k] * mult;
      }
    }
    determinant *= A->matrix[i][i];
  }
  determinant *= (double)swap;
  if (fabs(determinant) < EQ_LIMIT) determinant = 0.0f;
  return determinant;
}

double minor_det(const matrix_t *A, int row, int column, matrix_t *minor) {
  double determinant = 0.0f;
  for (int i = 0; i < minor->rows; i++) {
    int x = i;
    if (x >= row) {
      x++;
    }
    for (int j = 0; j < minor->columns; j++) {
      int y = j;
      if (y >= column) {
        y++;
      }
      minor->matrix[i][j] = A->matrix[x][y];
    }
  }
  determinant = gauss(minor);
  return determinant;
}

void alg_complements(const matrix_t *A, matrix_t *result) {
  matrix_t minor = {};
  s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = pow(-1, i + j) * minor_det(A, i, j, &minor);
    }
  }
  s21_remove_matrix(&minor);
  return;
}
