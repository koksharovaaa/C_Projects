#include "s21_decimal.h"

int get_bit(s21_decimal value, int index) {
  return !!(value.bits[index / 32] & (1u << (index % 32)));
}

void set_bit(s21_decimal *value, int index, int bit) {
  unsigned int mask = 1u << (index % 32);
  if (bit)
    value->bits[index / 32] |= mask;
  else
    value->bits[index / 32] &= ~mask;
  return;
}

int get_sign(s21_decimal value) { return !!(value.bits[3] & 0x80000000u); }

void set_sign(s21_decimal *value, int sign) {
  set_bit(value, DECSIGN, sign);
  return;
}

int get_scale(s21_decimal value) { return ((value.bits[3] & 0xFF0000u) >> 16); }

void set_scale(s21_decimal *value, int scale) {
  value->bits[3] &= 0x80000000u;
  scale = (scale << 16);
  value->bits[3] |= scale;
  return;
}

int is_zero(s21_decimal value) {
  return !(value.bits[0] || value.bits[1] || value.bits[2]);
}

int is_valid(s21_decimal value) {
  int res = 1;
  if (value.bits[3] & 0x00ffff) res = 0;
  int scale = get_scale(value);
  if (scale < 0 || scale > 28) res = 0;
  return res;
}
