#include "s21_decimal.h"

// Arithmetic Functions
// 0 - ok, 1 - decimal too big, 2 - decimal too small, 3 - division by 0

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big big_1 = to_big(value_1);
  big big_2 = to_big(value_2);
  big big_res = {0};
  *result = (s21_decimal){0};
  if (get_scale_big(big_1) != get_scale_big(big_2)) even_out(&big_1, &big_2);
  int comp = abs_comp(big_1, big_2);
  if (get_sign_big(big_1) == get_sign_big(big_2)) {
    addition(big_1, big_2, &big_res);
    int sign = get_sign(value_1);
    set_sign_big(&big_res, sign);
  } else if (comp > 0) {
    subtraction(big_1, big_2, &big_res);
    int sign = get_sign(value_1);
    set_sign_big(&big_res, sign);
  } else if (comp < 0) {
    subtraction(big_2, big_1, &big_res);
    int sign = get_sign(value_2);
    set_sign_big(&big_res, sign);
  }
  int scale = get_scale_big(big_1);
  set_scale_big(&big_res, scale);
  int res = to_dec(big_res, result);
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big big_1 = to_big(value_1);
  big big_2 = to_big(value_2);
  big big_res = {0};
  *result = (s21_decimal){0};
  if (get_scale_big(big_1) != get_scale_big(big_2)) even_out(&big_1, &big_2);
  int comp = abs_comp(big_1, big_2);
  if (get_sign_big(big_1) != get_sign_big(big_2)) {
    addition(big_1, big_2, &big_res);
    int sign = get_sign_big(big_1);
    set_sign_big(&big_res, sign);
  } else if (comp < 0) {
    subtraction(big_2, big_1, &big_res);
    if (!get_sign(value_1)) set_sign_big(&big_res, 1);
  } else if (comp > 0) {
    subtraction(big_1, big_2, &big_res);
    int sign = get_sign_big(big_1);
    set_sign_big(&big_res, sign);
  }
  int scale = get_scale_big(big_1);
  set_scale_big(&big_res, scale);
  int res = to_dec(big_res, result);
  return res;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big big_res = {0};
  *result = (s21_decimal){0};
  if (get_sign(value_1) != get_sign(value_2)) set_sign_big(&big_res, 1);
  for (int i = 0; i <= DECLAST; i++) {
    if (get_bit(value_2, i)) {
      big tmp_shift = to_big(value_1);
      shift_left_big(&tmp_shift, i);
      addition(big_res, tmp_shift, &big_res);
    }
  }
  int scale = get_scale(value_1) + get_scale(value_2);
  set_scale_big(&big_res, scale);
  int res = to_dec(big_res, result);
  return res;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = (s21_decimal){0};
  int res = 3;
  if (!is_zero(value_2)) {
    big big_1 = to_big(value_1);
    big big_2 = to_big(value_2);
    big big_res = {0};
    if (get_sign(value_1) != get_sign(value_2)) set_sign_big(&big_res, 1);
    corr_scale(&big_1, &big_2);
    division(&big_1, big_2, &big_res);
    while (!is_zero_big(big_1) && inc_scale(&big_1)) {
      inc_scale(&big_res);
      big tmp = {0};
      division(&big_1, big_2, &tmp);
      addition(big_res, tmp, &big_res);
    }
    int scale_1 = get_scale_big(big_1);
    set_scale_big(&big_res, scale_1);
    res = to_dec(big_res, result);
  }
  return res;
}
