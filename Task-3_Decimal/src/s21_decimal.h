#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECLAST 95
#define DECSIGN 127

#define BIGLAST 191
#define BIGSIGN 223

#define ONEBIG                      \
  (big) {                           \
    .bits = { 1, 0, 0, 0, 0, 0, 0 } \
  }

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} big;

// Main functions
// Arithmetic Functions
// 0 - ok, 1 - decimal too big, 2 - decimal too small, 3 - division by 0
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Functions
// 0 — false, 1 — true
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Conversion Functions
// 0 — ok, 1 — error
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Additional converters
// Other functions
// 0 — ok, 1 — error
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Additional functions
// Miscellaneous Functions
// Decimal
int get_bit(s21_decimal value, int bit);
void set_bit(s21_decimal *value, int index, int bit);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
int is_zero(s21_decimal value);
int is_valid(s21_decimal value);

// Big
int get_bit_big(big value, int bit);
void set_bit_big(big *value, int index, int bit);
int get_sign_big(big value);
void set_sign_big(big *value, int sign);
int get_scale_big(big value);
void set_scale_big(big *value, int scale);
int is_zero_big(big value);
int first_bit(big value);
void shift_left_big(big *value, int count);
void shift_right_big(big *value, int count);

// Big Converters
big to_big(s21_decimal decimal);
int to_dec(big value, s21_decimal *decimal);

// Big Arithmetic Functions
int abs_comp(big big_1, big big_2);
int inc_scale(big *value);
int dec_scale(big *value);
void corr_scale(big *big_1, big *big_2);
void even_out(big *big_1, big *big_2);
int addition(big value_1, big value_2, big *result);
void subtraction(big value_1, big value_2, big *result);
void division(big *big_1, big big_2, big *big_res);

#endif
