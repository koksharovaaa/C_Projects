#include "s21_decimal.h"

// Other functions
// 0 — ok, 1 — error

int s21_floor(s21_decimal value, s21_decimal *result) {
  *result = (s21_decimal){0};
  int res = 1;
  if (is_valid(value)) {
    res = 0;
    int rem = 0;
    big big_value = to_big(value);
    for (int i = get_scale(value); i > 0; i--) {
      int rem_temp = dec_scale(&big_value);
      if (rem_temp) rem = rem_temp;
    }
    if (rem && get_sign(value)) addition(big_value, ONEBIG, &big_value);
    to_dec(big_value, result);
  }
  return res;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  *result = (s21_decimal){0};
  int res = 1;
  if (is_valid(value)) {
    res = 0;
    int rem = 0;
    big big_value = to_big(value);
    for (int i = get_scale(value); i > 0; i--) {
      rem = dec_scale(&big_value);
    }
    if (rem > 4) addition(big_value, ONEBIG, &big_value);
    to_dec(big_value, result);
  }
  return res;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = (s21_decimal){0};
  int res = 1;
  if (is_valid(value)) {
    res = 0;
    big big_value = to_big(value);
    for (int i = get_scale(value); i > 0; i--) {
      dec_scale(&big_value);
    }
    to_dec(big_value, result);
  }
  return res;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = 1;
  *result = (s21_decimal){0};
  if (is_valid(value)) {
    res = 0;
    *result = value;
    if (get_sign(value))
      set_sign(result, 0);
    else
      set_sign(result, 1);
  }
  return res;
}
