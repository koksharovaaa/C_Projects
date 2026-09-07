#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int return_value = INCORRECT_MATRIX;
  if (result && rows > 0 && columns > 0) {
    return_value = OK;
    result->matrix = malloc(rows * sizeof(double *));
    if (result->matrix == NULL) return_value = INCORRECT_MATRIX;
    for (int i = 0; i < rows && !return_value; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        return_value = INCORRECT_MATRIX;
        for (int j = 0; j < i; j++) {
          free(result->matrix[i]);
        }
      }
    }
    if (!return_value) {
      result->rows = rows;
      result->columns = columns;
    }
  }
  return return_value;
}

void s21_remove_matrix(matrix_t *A) {
  if (is_matrix_valid(A)) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
  return;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int comparison = FAILURE;
  if (is_matrix_valid(A) && is_matrix_valid(B) && A->rows == B->rows &&
      A->columns == B->columns) {
    comparison = SUCCESS;
    int i = 0;
    while (comparison && i < A->rows) {
      int j = 0;
      while (comparison && j < A->columns) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) < EQ_LIMIT) {
          comparison = SUCCESS;
        } else {
          comparison = FAILURE;
        }
        j++;
      }
      i++;
    }
  }
  return comparison;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_value = OK;
  if (!is_matrix_valid(A) || !is_matrix_valid(B) || !result) {
    return_value = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    return_value = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && !return_value; i++) {
      for (int j = 0; j < A->columns && !return_value; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) return_value = CALC_ERROR;
      }
    }
  }
  return return_value;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_value = OK;
  if (!is_matrix_valid(A) || !is_matrix_valid(B) || !result) {
    return_value = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    return_value = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && !return_value; i++) {
      for (int j = 0; j < A->columns && !return_value; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) return_value = CALC_ERROR;
      }
    }
  }
  return return_value;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int return_value = INCORRECT_MATRIX;
  if (is_matrix_valid(A) && result) {
    s21_create_matrix(A->rows, A->columns, result);
    return_value = mult_num(A, number, result);
  }
  return return_value;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_value = OK;
  if (!is_matrix_valid(A) || !is_matrix_valid(B) || !result) {
    return_value = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    return_value = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    return_value = mult_mat(A, B, result);
  }
  return return_value;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_value = OK;
  if (!is_matrix_valid(A) || !result) {
    return_value = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    transpose(A, result);
  }
  return return_value;
}

int s21_determinant(matrix_t *A, double *result) {
  int return_value = OK;
  *result = 0.0f;
  if (!is_matrix_valid(A)) {
    return_value = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    return_value = CALC_ERROR;
  } else {
    *result = gauss(A);
  }
  return return_value;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int return_value = OK;
  if (!is_matrix_valid(A) || !result) {
    return_value = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    return_value = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    alg_complements(A, result);
  }
  return return_value;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int return_value = CALC_ERROR;
  if (!is_matrix_valid(A) || !result) {
    return_value = INCORRECT_MATRIX;
  } else if (A->columns == A->rows) {
    matrix_t tmp = {};
    s21_create_matrix(A->rows, A->columns, &tmp);
    copy_matrix(A, &tmp);
    double determinant = gauss(&tmp);
    if (determinant) {
      return_value = OK;
      determinant = 1 / determinant;
      s21_create_matrix(A->rows, A->columns, result);
      alg_complements(A, result);
      transpose(result, &tmp);
      mult_num(&tmp, determinant, result);
    }
    s21_remove_matrix(&tmp);
  }
  return return_value;
}
