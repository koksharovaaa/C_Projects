#include "s21_decimal.h"

// Big Arithmetic Functions
int abs_comp(big big_1, big big_2) {
  int res = 0;
  int i = BIGLAST;
  while (!res && i >= 0) {
    if (get_bit_big(big_1, i) > get_bit_big(big_2, i))
      res = 1;
    else if (get_bit_big(big_1, i) < get_bit_big(big_2, i))
      res = -1;
    i--;
  }
  return res;
}

int inc_scale(big *value) {
  int res = 0;
  int scale = get_scale_big(*value);
  if (first_bit(*value) < 186 && scale < 30) {
    big shift_1 = *value;
    big shift_3 = *value;
    set_scale_big(value, scale + 1);
    shift_left_big(&shift_1, 1);
    shift_left_big(&shift_3, 3);
    addition(shift_1, shift_3, value);
    res = 1;
  }
  return res;
}

int dec_scale(big *value) {
  big tmp_1 = *value, tmp_2 = *value;
  big tmp = {0};
  shift_right_big(&tmp_1, 1);
  shift_right_big(&tmp_2, 2);
  addition(tmp_1, tmp_2, &tmp);
  tmp_1 = tmp;
  shift_right_big(&tmp_1, 4);
  addition(tmp, tmp_1, &tmp);
  tmp_1 = tmp;
  shift_right_big(&tmp_1, 8);
  addition(tmp, tmp_1, &tmp);
  tmp_1 = tmp;
  shift_right_big(&tmp_1, 16);
  addition(tmp, tmp_1, &tmp);
  tmp_1 = tmp;
  shift_right_big(&tmp_1, 32);
  addition(tmp, tmp_1, &tmp);
  tmp_1 = tmp;
  shift_right_big(&tmp_1, 64);
  addition(tmp, tmp_1, &tmp);
  shift_right_big(&tmp, 3);
  tmp_1 = tmp;
  tmp_2 = tmp;  // rounding
  shift_left_big(&tmp_1, 1);
  shift_left_big(&tmp_2, 3);
  addition(tmp_1, tmp_2, &tmp_1);
  subtraction(*value, tmp_1, &tmp_2);
  if (tmp_2.bits[0] > 9) addition(tmp, ONEBIG, &tmp);
  tmp_1 = tmp;  // bank rounding
  tmp_2 = tmp;
  shift_left_big(&tmp_1, 1);
  shift_left_big(&tmp_2, 3);
  addition(tmp_1, tmp_2, &tmp_1);
  subtraction(*value, tmp_1, &tmp_2);
  int scale = get_scale_big(*value);
  int sign = get_sign_big(*value);
  *value = tmp;
  set_scale_big(value, 0);
  if (scale) set_scale_big(value, scale - 1);
  set_sign_big(value, sign);
  return tmp_2.bits[0];
}

void corr_scale(big *big_1, big *big_2) {
  int scale_1 = get_scale_big(*big_1);
  int scale_2 = get_scale_big(*big_2);
  if (scale_1 > scale_2) {
    for (int i = scale_1 - scale_2; i > 0; i--) {
      inc_scale(big_2);
    }
  } else if (scale_1 < scale_2) {
    for (int i = scale_2 - scale_1; i > 0; i--) {
      inc_scale(big_1);
    }
  }
  set_scale_big(big_1, 0);
  set_scale_big(big_2, 0);
  return;
}

void even_out(big *big_1, big *big_2) {
  int s1 = get_scale_big(*big_1);
  int s2 = get_scale_big(*big_2);
  while (s1 != s2) {
    if (s1 > s2) {
      inc_scale(big_2);
    } else {
      inc_scale(big_1);
    }
    s1 = get_scale_big(*big_1);
    s2 = get_scale_big(*big_2);
  }
  return;
}

int addition(big value_1, big value_2, big *result) {
  int overflow = 0;
  int bit = 0;
  for (int i = 0; i <= BIGLAST; i++) {
    bit = get_bit_big(value_1, i) + get_bit_big(value_2, i) + overflow;
    overflow = bit / 2;
    bit %= 2;
    set_bit_big(result, i, bit);
  }
  return overflow;
}

void subtraction(big value_1, big value_2, big *result) {
  big comp_2 = value_2;  // two's complement
  for (int i = 0; i < 6; i++) {
    comp_2.bits[i] = ~value_2.bits[i];
  }
  addition(comp_2, ONEBIG, &comp_2);
  addition(value_1, comp_2, result);
  return;
}

void division(big *big_1, big big_2, big *big_res) {
  int index_1 = first_bit(*big_1);
  int index_2 = first_bit(big_2);
  if (index_1 >= index_2) {
    shift_left_big(&big_2, index_1 - index_2);
    int quot_size = index_1 - index_2 + 1;
    while (quot_size > 0) {
      shift_left_big(big_res, 1);
      if ((abs_comp(*big_1, big_2) >= 0)) {
        subtraction(*big_1, big_2, big_1);
        shift_right_big(&big_2, 1);
        set_bit_big(big_res, 0, 1);
      } else {
        shift_right_big(&big_2, 1);
      }
      quot_size--;
    }
  }
  return;
}
