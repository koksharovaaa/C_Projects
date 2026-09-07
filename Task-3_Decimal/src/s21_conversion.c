#include "s21_decimal.h"

// Conversion Functions
// 0 — ok, 1 — error

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  *dst = (s21_decimal){0};
  if (src < 0) {
    set_sign(dst, 1);
    src = -src;
  }
  dst->bits[0] = src;
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  *dst = (s21_decimal){0};
  int res = 0;
  if (src > pow(2, 95) || src < (-1) * pow(2, 96)) {
    res = 1;
  } else if (src < pow(10, -28) && src > 0) {
    res = 1;
  } else if (src > (-1) * pow(10, -28) && src < 0) {
    res = 1;
  } else {
    int len = snprintf(NULL, 0, "%.28lf", src);
    char *str = (char *)malloc((len + 1) * sizeof(char));
    snprintf(str, len + 1, "%.28lf", src);
    big result = {0};
    for (int i = 0; i < len; i++) {
      if (str[i] == '-') {
        set_sign_big(&result, 1);
      } else if (str[i] == '.') {
        set_scale_big(&result, 0);
      } else {
        inc_scale(&result);
        big tmp = {{str[i] - '0', 0, 0, 0, 0, 0, 0}};
        addition(result, tmp, &result);
      }
    }
    free(str);
    if (to_dec(result, dst)) res = 1;
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 1;
  *dst = 0;
  if (is_valid(src)) {
    s21_truncate(src, &src);
    if (!src.bits[2] && !src.bits[1] && !get_bit(src, 31)) {
      res = 0;
      int tmp = src.bits[0];
      if (get_sign(src)) tmp = -tmp;
      *dst = tmp;
    }
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 1;
  *dst = 0.0;
  if (is_valid(src)) {
    double tmp = 0.0;
    res = 0;
    for (int i = 0; i <= DECLAST; i++) {
      if (get_bit(src, i)) tmp += pow(2, i);
    }
    for (int i = get_scale(src); i > 0; i--) {
      tmp /= 10;
    }
    if (get_sign(src)) tmp *= (-1);
    *dst = tmp;
  }
  return res;
}

// Big Converters
// to_dec
// 0 - ok, 1 - decimal too big, 2 - decimal too small

big to_big(s21_decimal decimal) {
  big value = {0};
  for (int i = 0; i < 3; i++) {
    value.bits[i] = decimal.bits[i];
  }
  value.bits[6] = decimal.bits[3];
  return value;
}

int to_dec(big value, s21_decimal *decimal) {
  *decimal = (s21_decimal){0};
  int res = 0;
  int r = 0;
  while (get_scale_big(value) > 28) {
    r = dec_scale(&value);
  }
  if ((r > 4 && get_bit_big(value, 0)) || r > 5)
    addition(value, ONEBIG, &value);
  while (first_bit(value) > 95 && get_scale_big(value)) {
    r = dec_scale(&value);
    if (first_bit(value) <= 95 && ((r > 4 && get_bit_big(value, 0)) || r > 5))
      addition(value, ONEBIG, &value);
  }
  if (first_bit(value) < 96) {
    for (int i = 0; i < 3; i++) {
      decimal->bits[i] = value.bits[i];
    }
    decimal->bits[3] = value.bits[6];
  } else if (get_sign_big(value)) {
    res = 2;
  } else {
    res = 1;
  }
  return res;
}
