#include "s21_decimal.h"

// Comparison Functions
// 0 — false, 1 — true

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (sign_1 > sign_2 && !(is_zero(value_1) && is_zero(value_2))) {
    res = 1;
  } else if (sign_1 == sign_2) {
    big big_1 = to_big(value_1);
    big big_2 = to_big(value_2);
    if (get_scale_big(big_1) != get_scale_big(big_2)) even_out(&big_1, &big_2);
    int comp = abs_comp(big_1, big_2);
    if (sign_1 && comp > 0)
      res = 1;
    else if (!sign_1 && comp < 0)
      res = 1;
  }
  return res;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (is_zero(value_1) && is_zero(value_2)) {
    res = 1;
  } else if (sign_1 > sign_2) {
    res = 1;
  } else if (sign_1 == sign_2) {
    big big_1 = to_big(value_1);
    big big_2 = to_big(value_2);
    if (get_scale_big(big_1) != get_scale_big(big_2)) even_out(&big_1, &big_2);
    int comp = abs_comp(big_1, big_2);
    if (comp == 0)
      res = 1;
    else if (sign_1 && comp > 0)
      res = 1;
    else if (!sign_1 && comp < 0)
      res = 1;
  }
  return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (sign_1 < sign_2 && !(is_zero(value_1) && is_zero(value_2))) {
    res = 1;
  } else if (sign_1 == sign_2) {
    big big_1 = to_big(value_1);
    big big_2 = to_big(value_2);
    if (get_scale_big(big_1) != get_scale_big(big_2)) even_out(&big_1, &big_2);
    int comp = abs_comp(big_1, big_2);
    if (sign_1 && comp < 0)
      res = 1;
    else if (!sign_1 && comp > 0)
      res = 1;
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (is_zero(value_1) && is_zero(value_2)) {
    res = 1;
  } else if (sign_1 < sign_2) {
    res = 1;
  } else if (sign_1 == sign_2) {
    big big_1 = to_big(value_1);
    big big_2 = to_big(value_2);
    if (get_scale_big(big_1) != get_scale_big(big_2)) even_out(&big_1, &big_2);
    int comp = abs_comp(big_1, big_2);
    if (comp == 0)
      res = 1;
    else if (sign_1 && comp < 0)
      res = 1;
    else if (!sign_1 && comp > 0)
      res = 1;
  }
  return res;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (is_zero(value_1) && is_zero(value_2)) {
    res = 1;
  } else if (sign_1 == sign_2) {
    big big_1 = to_big(value_1);
    big big_2 = to_big(value_2);
    if (get_scale_big(big_1) != get_scale_big(big_2)) even_out(&big_1, &big_2);
    if (!abs_comp(big_1, big_2)) res = 1;
  }
  return res;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !(s21_is_equal(value_1, value_2));
}
