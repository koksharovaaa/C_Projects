#include "s21_decimal.h"

int get_bit_big(big value, int index) {
  return !!(value.bits[index / 32] & (1u << (index % 32)));
}

void set_bit_big(big *value, int index, int bit) {
  unsigned int mask = 1u << (index % 32);
  if (bit)
    value->bits[index / 32] |= mask;
  else
    value->bits[index / 32] &= ~mask;
  return;
}

int get_sign_big(big value) { return !!(value.bits[6] & 0x80000000u); }

void set_sign_big(big *value, int sign) {
  set_bit_big(value, BIGSIGN, sign);
  return;
}

int get_scale_big(big value) { return ((value.bits[6] & 0xFF0000u) >> 16); }

void set_scale_big(big *value, int scale) {
  value->bits[6] &= 0x80000000u;
  scale = (scale << 16);
  value->bits[6] |= scale;
  return;
}

int first_bit(big value) {
  int index = -1;
  int i = BIGLAST;
  while (index == -1 && i >= 0) {
    if (get_bit_big(value, i)) index = i;
    i--;
  }
  return index;
}

int is_zero_big(big value) {
  return !(value.bits[0] || value.bits[1] || value.bits[2] || value.bits[3] ||
           value.bits[4] || value.bits[5]);
}

void shift_left_big(big *value, int count) {
  int tmp_bit = 0;
  int bit = 0;
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < 6; j++) {
      bit = get_bit_big(*value, j * 32 + 31);
      value->bits[j] = value->bits[j] << 1;
      if (j > 0) set_bit_big(value, j * 32, tmp_bit);
      tmp_bit = bit;
    }
  }
  return;
}

void shift_right_big(big *value, int count) {
  int tmp_bit = 0;
  int bit = 0;
  for (int i = 0; i < count; i++) {
    for (int j = 5; j >= 0; j--) {
      bit = get_bit_big(*value, j * 32);
      value->bits[j] = value->bits[j] >> 1;
      if (j < 5)
        set_bit_big(value, j * 32 + 31, tmp_bit);
      else
        set_bit_big(value, j * 32 + 31, 0);
      tmp_bit = bit;
    }
  }
  return;
}
