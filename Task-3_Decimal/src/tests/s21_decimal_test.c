#include "../s21_decimal.h"

#include <check.h>
#include <limits.h>
#include <stdio.h>

// Miscellaneous Functions Decimal
START_TEST(get_bit_0) {
  s21_decimal value = {{0, 0xffff, 0, 0}};
  ck_assert_int_eq(0, get_bit(value, 48));
}
END_TEST

START_TEST(get_bit_1) {
  s21_decimal value = {{0, 1, 0, 0}};
  ck_assert_int_eq(1, get_bit(value, 32));
}
END_TEST

START_TEST(set_bit_0) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_bit(&value, 48, 0);
  ck_assert_int_eq(0, get_bit(value, 48));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(0, value.bits[3]);
}
END_TEST

START_TEST(set_bit_1) {
  s21_decimal value = {0};
  set_bit(&value, 48, 1);
  ck_assert_int_eq(1, get_bit(value, 48));
  ck_assert_int_eq(0, value.bits[0]);
  ck_assert_int_eq(0, value.bits[2]);
  ck_assert_int_eq(0, value.bits[3]);
}
END_TEST

START_TEST(get_sign_0) {
  s21_decimal value = {0};
  ck_assert_int_eq(0, get_sign(value));
}
END_TEST

START_TEST(get_sign_1) {
  s21_decimal value = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(1, get_sign(value));
}
END_TEST

START_TEST(set_sign_0) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80000000}};
  set_sign(&value, 0);
  ck_assert_int_eq(0, get_sign(value));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
}
END_TEST

START_TEST(set_sign_1) {
  s21_decimal value = {0};
  set_sign(&value, 1);
  ck_assert_int_eq(1, get_sign(value));
  ck_assert_int_eq(0, value.bits[0]);
  ck_assert_int_eq(0, value.bits[1]);
  ck_assert_int_eq(0, value.bits[2]);
}
END_TEST

START_TEST(get_scale_0) {
  s21_decimal value = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(0, get_scale(value));
}
END_TEST

START_TEST(get_scale_1) {
  s21_decimal value = {{0, 0, 0, 0x80110000}};
  ck_assert_int_eq(17, get_scale(value));
}
END_TEST

START_TEST(set_scale_0) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80110000}};
  set_scale(&value, 0);
  ck_assert_int_eq(1, get_sign(value));
  ck_assert_int_eq(0, get_scale(value));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
}
END_TEST

START_TEST(set_scale_1) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80000000}};
  set_scale(&value, 28);
  ck_assert_int_eq(1, get_sign(value));
  ck_assert_int_eq(28, get_scale(value));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
}
END_TEST

START_TEST(is_zero_0) {
  s21_decimal value = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(1, is_zero(value));
}

START_TEST(is_zero_1) {
  s21_decimal value = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(0, is_zero(value));
}

START_TEST(is_zero_2) {
  s21_decimal value = {{0, UINT_MAX, 0, 0}};
  ck_assert_int_eq(0, is_zero(value));
}

START_TEST(is_zero_3) {
  s21_decimal value = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(0, is_zero(value));
}

START_TEST(is_valid_0) {
  s21_decimal value = {{0, 0, 0, UINT_MAX}};
  ck_assert_int_eq(0, is_valid(value));
}

START_TEST(is_valid_1) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80000000}};
  ck_assert_int_eq(1, is_valid(value));
}

START_TEST(is_valid_2) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_scale(&value, -1);
  ck_assert_int_eq(0, is_valid(value));
}

START_TEST(is_valid_3) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_scale(&value, 30);
  ck_assert_int_eq(0, is_valid(value));
}

START_TEST(is_valid_4) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0xffff}};
  set_scale(&value, 30);
  ck_assert_int_eq(0, is_valid(value));
}

// Miscellaneous Functions Big
START_TEST(get_bit_big_0) {
  big value = {{0, 0, 0, 0, 0, 0xffff, 0}};
  ck_assert_int_eq(0, get_bit_big(value, 176));
}
END_TEST

START_TEST(get_bit_big_1) {
  big value = {{0, 0, 0, 0, 0, 1, 0}};
  ck_assert_int_eq(1, get_bit_big(value, 160));
}
END_TEST

START_TEST(set_bit_big_0) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_bit_big(&value, 176, 0);
  ck_assert_int_eq(0, get_bit_big(value, 176));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(UINT_MAX, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(0, value.bits[6]);
}
END_TEST

START_TEST(set_bit_big_1) {
  big value = {{0, 0, 0, 0, 0, 0, 0x80000000}};
  set_bit_big(&value, 160, 1);
  ck_assert_int_eq(1, get_bit_big(value, 160));
  ck_assert_int_eq(0, value.bits[0]);
  ck_assert_int_eq(0, value.bits[1]);
  ck_assert_int_eq(0, value.bits[2]);
  ck_assert_int_eq(0, value.bits[3]);
  ck_assert_int_eq(0, value.bits[4]);
  ck_assert_int_eq(0x80000000, value.bits[6]);
}
END_TEST

START_TEST(get_sign_big_0) {
  big value = {0};
  ck_assert_int_eq(0, get_sign_big(value));
}
END_TEST

START_TEST(get_sign_big_1) {
  big value = {{0, 0, 0, 0, 0, 0, 0x80000000}};
  ck_assert_int_eq(1, get_sign_big(value));
}
END_TEST

START_TEST(set_sign_big_0) {
  big value = {
      {UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0x80000000}};
  set_sign_big(&value, 0);
  ck_assert_int_eq(0, get_sign_big(value));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(UINT_MAX, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(UINT_MAX, value.bits[5]);
}
END_TEST

START_TEST(set_sign_big_1) {
  big value = {0};
  set_sign_big(&value, 1);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(0, value.bits[0]);
  ck_assert_int_eq(0, value.bits[1]);
  ck_assert_int_eq(0, value.bits[2]);
  ck_assert_int_eq(0, value.bits[3]);
  ck_assert_int_eq(0, value.bits[4]);
  ck_assert_int_eq(0, value.bits[5]);
}
END_TEST

START_TEST(get_scale_big_0) {
  big value = {{0, 0, 0, 0, 0, 0, 0x80000000}};
  ck_assert_int_eq(0, get_scale_big(value));
}
END_TEST

START_TEST(get_scale_big_1) {
  big value = {{0, 0, 0, 0, 0, 0, 0x80110000}};
  ck_assert_int_eq(17, get_scale_big(value));
}
END_TEST

START_TEST(set_scale_big_0) {
  big value = {
      {UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0x110000}};
  set_sign_big(&value, 1);
  set_scale_big(&value, 0);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(0, get_scale_big(value));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(UINT_MAX, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(UINT_MAX, value.bits[5]);
}
END_TEST

START_TEST(set_scale_big_1) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign_big(&value, 1);
  set_scale_big(&value, 28);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(28, get_scale_big(value));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(UINT_MAX, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(UINT_MAX, value.bits[5]);
}
END_TEST

START_TEST(is_zero_big_0) {
  big value = {{0, 0, 0, 0, 0, 0, 0x80000000}};
  ck_assert_int_eq(1, is_zero_big(value));
}

START_TEST(is_zero_big_1) {
  big value = {{
      UINT_MAX,
      0,
      0,
      0,
      0,
      0,
      0,
  }};
  ck_assert_int_eq(0, is_zero_big(value));
}

START_TEST(is_zero_big_2) {
  big value = {{0, UINT_MAX, 0, 0, 0, 0, 0}};
  ck_assert_int_eq(0, is_zero_big(value));
}

START_TEST(is_zero_big_3) {
  big value = {{0, 0, UINT_MAX, 0, 0, 0, 0}};
  ck_assert_int_eq(0, is_zero_big(value));
}

START_TEST(first_bit_big_0) {
  big value = {0};
  set_sign_big(&value, 1);
  ck_assert_int_eq(-1, first_bit(value));
}
END_TEST

START_TEST(first_bit_big_1) {
  big value = {0};
  set_bit_big(&value, 171, 1);
  ck_assert_int_eq(171, first_bit(value));
}
END_TEST

START_TEST(shift_left_big_0) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign_big(&value, 1);
  set_scale_big(&value, 28);
  shift_left_big(&value, 32);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(28, get_scale_big(value));
  ck_assert_int_eq(0, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(UINT_MAX, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(UINT_MAX, value.bits[5]);
}
END_TEST

START_TEST(shift_left_big_1) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0, 0}};
  set_sign_big(&value, 1);
  set_scale_big(&value, 28);
  shift_left_big(&value, 16);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(28, get_scale_big(value));
  ck_assert_int_eq(0xffff0000, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(UINT_MAX, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(0xffff, value.bits[5]);
}
END_TEST

START_TEST(shift_left_big_2) {
  big value = {{UINT_MAX, 0, 0, 0, 0, 0, 0}};
  set_sign_big(&value, 1);
  set_scale_big(&value, 28);
  shift_left_big(&value, 128);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(28, get_scale_big(value));
  ck_assert_int_eq(0, value.bits[0]);
  ck_assert_int_eq(0, value.bits[1]);
  ck_assert_int_eq(0, value.bits[2]);
  ck_assert_int_eq(0, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(0, value.bits[5]);
}
END_TEST

START_TEST(shift_right_big_0) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign_big(&value, 1);
  set_scale_big(&value, 28);
  shift_right_big(&value, 32);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(28, get_scale_big(value));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(UINT_MAX, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(0, value.bits[5]);
}
END_TEST

START_TEST(shift_right_big_1) {
  big value = {{0, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign_big(&value, 1);
  set_scale_big(&value, 28);
  shift_right_big(&value, 16);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(28, get_scale_big(value));
  ck_assert_int_eq(0xffff0000, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(UINT_MAX, value.bits[2]);
  ck_assert_int_eq(UINT_MAX, value.bits[3]);
  ck_assert_int_eq(UINT_MAX, value.bits[4]);
  ck_assert_int_eq(0xffff, value.bits[5]);
}
END_TEST

START_TEST(shift_right_big_2) {
  big value = {{0, 0, 0, 0, UINT_MAX, UINT_MAX, 0}};
  set_sign_big(&value, 1);
  set_scale_big(&value, 28);
  shift_right_big(&value, 128);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(28, get_scale_big(value));
  ck_assert_int_eq(UINT_MAX, value.bits[0]);
  ck_assert_int_eq(UINT_MAX, value.bits[1]);
  ck_assert_int_eq(0, value.bits[2]);
  ck_assert_int_eq(0, value.bits[3]);
  ck_assert_int_eq(0, value.bits[4]);
  ck_assert_int_eq(0, value.bits[5]);
}
END_TEST

// Conversion Functions
START_TEST(big_to_decimal_0) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0, 0, 0, 0x800f0000u}};
  s21_decimal dec_1 = {0};
  s21_decimal dec_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x800f0000u}};
  int result = to_dec(value, &dec_1);
  ck_assert_int_eq(1, s21_is_equal(dec_1, dec_2));
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(big_to_decimal_1) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal dec = {0};
  int result = to_dec(value, &dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(big_to_decimal_2) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign_big(&value, 1);
  s21_decimal dec = {0};
  int result = to_dec(value, &dec);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(big_to_decimal_3) {
  big value = {{0x0, 0x0, 0x0, 0x1, 0, 0, 0x80010000u}};
  s21_decimal dec_1 = {0};
  s21_decimal dec_2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000u}};
  int result = to_dec(value, &dec_1);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(1, s21_is_equal(dec_1, dec_2));
}
END_TEST

START_TEST(decimal_to_big_0) {
  s21_decimal value = {{1, 1, 1, 0x801c0000}};
  big big_1 = to_big(value);
  big big_2 = {{1, 1, 1, 0, 0, 0, 0x801c0000}};
  ck_assert_int_eq(abs_comp(big_1, big_2), 0);
  ck_assert_int_eq(big_1.bits[6], big_2.bits[6]);
}
END_TEST

// Arithmetic Functions Big
START_TEST(abs_comp_0) {
  big value_1 = {{0x0, 0x0, 0x0, 0x1, 0, 0, 0x80010000u}};
  big value_2 = {{0x0, 0x0, 0x0, 0x2, 0, 0, 0x80010000u}};
  ck_assert_int_eq(-1, abs_comp(value_1, value_2));
}
END_TEST

START_TEST(abs_comp_1) {
  big value_1 = {{0x0, 0x0, 0x0, 0x1, 0, 0, 0x80010000u}};
  big value_2 = {{0x0, 0x0, UINT_MAX, 0, 0, 0, 0x80010000u}};
  ck_assert_int_eq(1, abs_comp(value_1, value_2));
}
END_TEST

START_TEST(abs_comp_2) {
  big value_1 = {{0x0, 0x0, UINT_MAX, 0, 0, 0, 0x80010000u}};
  big value_2 = {{0x0, 0x0, UINT_MAX, 0, 0, 0, 0x80010000u}};
  ck_assert_int_eq(0, abs_comp(value_1, value_2));
}
END_TEST

START_TEST(inc_scale_0) {
  big value = {{UINT_MAX, 0x0, 0x0, 0, 0, 0, 0x80000000u}};
  big check = {{0xfffffff6, 0x9, 0x0, 0, 0, 0, 0x80010000u}};
  int result = inc_scale(&value);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(0, abs_comp(value, check));
  ck_assert_int_eq(1, get_scale_big(value));
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(inc_scale_1) {
  big value = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_scale_big(&value, 5);
  big check = value;
  int result = inc_scale(&value);
  ck_assert_int_eq(0, abs_comp(value, check));
  ck_assert_int_eq(5, get_scale_big(value));
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(inc_scale_2) {
  big value = {{0x20, 0, 0, 0, 0, 0, 0x80110000}};
  big check = {{0x140, 0, 0, 0, 0, 0, 0x80120000}};
  int result = inc_scale(&value);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(0, abs_comp(value, check));
  ck_assert_int_eq(18, get_scale_big(value));
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(inc_scale_3) {
  big value = {{0x99999999, 0x99999999, 0x19999999, 0, 0, 0, 0}};
  big check = {{0xfffffffa, 0xffffffff, 0xffffffff, 0, 0, 0, 0x10000u}};
  int result = inc_scale(&value);
  ck_assert_int_eq(0, get_sign_big(value));
  ck_assert_int_eq(0, abs_comp(value, check));
  ck_assert_int_eq(1, get_scale_big(value));
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(dec_scale_0) {
  big value = {{0xfffffff8, 0x9, 0x0, 0, 0, 0, 0x80050000u}};
  big check = {{UINT_MAX, 0x0, 0x0, 0, 0, 0, 0x80040000u}};
  int result = dec_scale(&value);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(4, get_scale_big(value));
  ck_assert_int_eq(0, abs_comp(value, check));
  ck_assert_int_eq(2, result);
}
END_TEST

START_TEST(dec_scale_1) {
  big value = {{0x140, 0, 0, 0, 0, 0, 0x801c0000}};
  big check = {{0x20, 0, 0, 0, 0, 0, 0x80110000}};
  int result = dec_scale(&value);
  ck_assert_int_eq(1, get_sign_big(value));
  ck_assert_int_eq(27, get_scale_big(value));
  ck_assert_int_eq(0, abs_comp(value, check));
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(dec_scale_2) {
  big value = {{0xffff8481, 0x9fff, 0x0, 0, 0, 0, 0x110000u}};
  big check = {{0xfffff3a6, 0xfff, 0x0, 0, 0, 0, 0x100000u}};
  int result = dec_scale(&value);
  ck_assert_int_eq(16, get_scale_big(value));
  ck_assert_int_eq(0, abs_comp(value, check));
  ck_assert_int_eq(5, result);
}
END_TEST

START_TEST(dec_scale_3) {
  big value = {{0x0, 0x0, 0x0, 0x1, 0, 0, 0x10000u}};
  big check = {{0x99999999, 0x99999999, 0x19999999, 0, 0, 0, 0}};
  int result = dec_scale(&value);
  ck_assert_int_eq(0, get_scale_big(value));
  ck_assert_int_eq(0, abs_comp(value, check));
  ck_assert_int_eq(6, result);
}
END_TEST

// START_TEST(even_out_0) {} END_TEST
// START_TEST(corr_scale_0) {} END_TEST

START_TEST(addition_0) {
  big value_1 = {{0xffffffff, 0, 0, 0, 0, 0, 0x80110000}};
  big value_2 = {{0xffffffff, 0, 0, 0, 0, 0, 0x80110000}};
  big check = {{0xfffffffe, 0x1, 0, 0, 0, 0, 0}};
  big res = {0};
  int result = addition(value_1, value_2, &res);
  ck_assert_int_eq(0, get_scale_big(res));
  ck_assert_int_eq(0, get_sign_big(res));
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(addition_1) {
  big value_1 = {{0xfffffffa, 0xf, 0, 0, 0, 0, 0x80110000}};
  big value_2 = {{0xbcdfffff, 0, 0, 0, 0, 0, 0x80110000}};
  big check = {{0xbcdffff9, 0x10, 0, 0, 0, 0, 0}};
  big res = {0};
  int result = addition(value_1, value_2, &res);
  ck_assert_int_eq(0, get_scale_big(res));
  ck_assert_int_eq(0, get_sign_big(res));
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(addition_2) {
  big value_1 = {{0xffffffff, 0, 0, 0, 0, 0, 0}};
  big value_2 = {{0, 0, 0, 0xffffffff, 0, 0, 0}};
  big check = {{0xffffffff, 0, 0, 0xffffffff, 0, 0, 0}};
  big res = {0};
  int result = addition(value_1, value_2, &res);
  ck_assert_int_eq(0, get_scale_big(res));
  ck_assert_int_eq(0, get_sign_big(res));
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(subtraction_0) {
  big value_1 = {{0xfffffffe, 0x1, 0, 0, 0, 0, 0x80110000}};
  big value_2 = {{0xffffffff, 0, 0, 0, 0, 0, 0x80110000}};
  big check = {{0xffffffff, 0, 0, 0, 0, 0, 0}};
  big res = {0};
  subtraction(value_1, value_2, &res);
  ck_assert_int_eq(0, get_scale_big(res));
  ck_assert_int_eq(0, get_sign_big(res));
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(subtraction_1) {
  big value_2 = {{0xbcdfffff, 0, 0, 0, 0, 0, 0x80110000}};
  big value_1 = {{0xbcdffff9, 0x10, 0, 0, 0, 0, 0x80110000}};
  big check = {{0xfffffffa, 0xf, 0, 0, 0, 0, 0}};
  big res = {0};
  subtraction(value_1, value_2, &res);
  ck_assert_int_eq(0, get_scale_big(res));
  ck_assert_int_eq(0, get_sign_big(res));
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(subtraction_2) {
  big value_1 = {{0xffffffff, 0, 0, 0xffffffff, 0, 0, 0}};
  big value_2 = {{0xffffffff, 0, 0, 0, 0, 0, 0}};
  big check = {{0, 0, 0, 0xffffffff, 0, 0, 0}};
  big res = {0};
  subtraction(value_1, value_2, &res);
  ck_assert_int_eq(0, get_scale_big(res));
  ck_assert_int_eq(0, get_sign_big(res));
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(subtraction_3) {
  big value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 0, 0, 0}};
  big value_2 = {{0xff, UINT_MAX, UINT_MAX, UINT_MAX, 0, 0, 0}};
  big check = {{0xffffff00, 0, 0, 0, 0, 0, 0}};
  big res = {0};
  subtraction(value_1, value_2, &res);
  ck_assert_int_eq(0, get_scale_big(res));
  ck_assert_int_eq(0, get_sign_big(res));
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(division_0) {
  big big_1 = {{150, 0, 0, 0, 0, 0, 0}};
  big big_2 = {{50, 0, 0, 0, 0, 0, 0x80000000u}};
  big check = {{3, 0, 0, 0, 0, 0, 0}};
  big res = {0};
  division(&big_1, big_2, &res);
  ck_assert_int_eq(get_sign_big(check), get_sign_big(res));
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(division_1) {
  big big_1 = {{0xffffffff, 0xffffffff, 0, 0, 0, 0, 0}};
  big big_2 = {{0xffffffff, 0, 0, 0, 0, 0, 0x80000000u}};
  big check = {{0x1, 0x1, 0, 0, 0, 0, 0}};
  big res = {0};
  division(&big_1, big_2, &res);
  ck_assert_int_eq(get_sign_big(check), get_sign_big(res));
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

START_TEST(division_2) {
  big big_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0, 0, 0}};
  big big_2 = {{0x5, 0, 0, 0, 0, 0, 0x80000000u}};
  big check = {{0x33333333, 0x33333333, 0x33333333, 0x33333333, 0, 0, 0}};
  big res = {0};
  division(&big_1, big_2, &res);
  ck_assert_int_eq(get_sign_big(check), get_sign_big(res));
  ck_assert_int_eq(0, abs_comp(res, check));
}
END_TEST

// Arithmetic Functions Decimal
START_TEST(s21_add_0) {
  s21_decimal value_1 = {{0x40652, 0x0, 0x0, 0x10000}};
  s21_decimal value_2 = {{0x4c329922, 0x1b79e8d0, 0x5b996, 0x70000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xb5a351a2, 0x1b79e90d, 0x5b996, 0x70000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_1) {
  s21_decimal value_1 = {{0xde22b3bd, 0x5f3, 0x0, 0x90000}};
  s21_decimal value_2 = {{0x8b7051d8, 0x9, 0x0, 0x80040000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x64bf8343, 0xe8a70, 0x0, 0x80090000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal value_1 = {{0x21d9a969, 0x4b9278e, 0x0, 0x80040000}};
  s21_decimal value_2 = {{0x425ac7f, 0x0, 0x0, 0x80070000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x3e636ea7, 0x73428334, 0x12, 0x80070000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal value_1 = {{0x4377398a, 0xfaf, 0x0, 0x800d0000}};
  s21_decimal value_2 = {{0x1c53e1a0, 0xc70bdf18, 0x0, 0x130000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xdd6614e0, 0x28483019, 0x0, 0x80130000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal value_1 = {{0x294c5a0, 0x0, 0x0, 0x70000}};
  s21_decimal value_2 = {{0xbe50e630, 0x45ba517d, 0x0, 0x800b0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xeae92c30, 0x45ba5118, 0x0, 0x800b0000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal value_1 = {{0x3d6a6cc9, 0x0, 0x0, 0x80080000}};
  s21_decimal value_2 = {{0x6f833352, 0x8f, 0x0, 0x10000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xdcf14837, 0x557e88f4, 0x0, 0x80000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal value_1 = {{0x5ecb2, 0x0, 0x0, 0x50000}};
  s21_decimal value_2 = {{0xe35b2a7a, 0x33a0f770, 0x3, 0x800a0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xd9100f3a, 0x33a0f767, 0x3, 0x800a0000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal value_1 = {{0xe377486, 0x53abea99, 0x1, 0x40000}};
  s21_decimal value_2 = {{0x8850cf48, 0x67eb54fb, 0x16e, 0x50000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x167b5c84, 0xaca27ef6, 0x17b, 0x50000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal value_1 = {{0xe6a03cc, 0x1, 0x0, 0x80020000}};
  s21_decimal value_2 = {{0xc046e2da, 0x231b46, 0x0, 0x70000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x3c3bbb5a, 0x217ea8, 0x0, 0x70000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal value_1 = {{0x5b25a3f1, 0x1240c, 0x0, 0x80040000}};
  s21_decimal value_2 = {{0x18787840, 0x4f8148d5, 0x12a9a5, 0x170000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xf9772900, 0xc1e2467d, 0x67c1a285, 0x80120000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal value_1 = {{0x9e529a0a, 0x98ecdd18, 0x2f, 0x80120000}};
  s21_decimal value_2 = {{0x244b0a6, 0x0, 0x0, 0x80070000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xfaed0a0a, 0xcdbd1b68, 0x2f, 0x80120000}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_0) {
  s21_decimal value_1 = {{0xb1198b0d, 0x3d06802e, 0x211af, 0x100000}};
  s21_decimal value_2 = {{0x523894f1, 0xac159f42, 0x61, 0x50000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xbfb363e, 0xb62a23c2, 0x3a379873, 0x800c0000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_1) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal res1 = {0};
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  int res = 99899;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res, res_s21);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal value_1 = {{0x38ba2a03, 0xb82beace, 0xe52, 0x800a0000}};
  s21_decimal value_2 = {{0xeb6c6256, 0x2b, 0x0, 0x800c0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x3d4c06d6, 0xf127b862, 0x5984f, 0x800c0000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal value_1 = {{0x72198dd8, 0x517b04f2, 0x5, 0x80070000}};
  s21_decimal value_2 = {{0x3c19a30, 0x0, 0x0, 0x80000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x78c124a0, 0x2ece3178, 0x35, 0x80080000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal value_1 = {{0x65b45443, 0xb105f0ba, 0x10f4, 0x110000}};
  s21_decimal value_2 = {{0x59d60b15, 0x5297, 0x0, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x807b9443, 0x1d7bded1, 0x1d57b185, 0x110000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal value_1 = {{0x843efac, 0x4705acf5, 0x2d, 0x800d0000}};
  s21_decimal value_2 = {{0x712146e2, 0xec82ccfc, 0x4180b, 0x110000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x4ee375a2, 0x3a36f08f, 0xb00b2, 0x80110000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal value_1 = {{0xe6c74338, 0x1485, 0x0, 0x80010000}};
  s21_decimal value_2 = {{0xe2f186b9, 0x13c02898, 0x1af1ac, 0x800c0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x9236c6b9, 0x269f5aab, 0x1913d5, 0xc0000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal value_1 = {{0x211fe, 0x0, 0x0, 0x80050000}};
  s21_decimal value_2 = {{0xef18b303, 0x7b016a46, 0x81, 0x80050000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xef16a105, 0x7b016a46, 0x81, 0x50000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_8) {
  s21_decimal value_1 = {{0x5d7d835e, 0x434b, 0x0, 0xc0000}};
  s21_decimal value_2 = {{0x4296b2b9, 0x86e, 0x0, 0x70000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xd4f80642, 0xcdcfb0f, 0x0, 0x800c0000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_9) {
  s21_decimal value_1 = {{0x782fa7ca, 0x2, 0x0, 0x20000}};
  s21_decimal value_2 = {{0xa202478e, 0xaa4b55ca, 0x2c677, 0x80150000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xfab50728, 0x9227e64a, 0x22459f71, 0x140000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_10) {
  s21_decimal value_1 = {{0x5c103569, 0x1e19, 0x0, 0x80010000}};
  s21_decimal value_2 = {{0x5c45534, 0x0, 0x0, 0x70000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x58bdc174, 0xcb467506, 0x1, 0x80070000}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_0) {
  s21_decimal value_1 = {{0x6a47b6bb, 0x6, 0x0, 0x80050000}};
  s21_decimal value_2 = {{0x6256a2f4, 0x34699587, 0x24, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xd08d01aa, 0xc9c65497, 0x3b755460, 0x30000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_1) {
  s21_decimal value_1 = {{0x9b70a97b, 0x25233a, 0x0, 0x800c0000}};
  s21_decimal value_2 = {{0x5190a57, 0x0, 0x0, 0x50000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x2deb66cd, 0x15c1a44d, 0xbd52, 0x80110000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal value_1 = {{0x9431d604, 0x278b, 0x0, 0x80040000}};
  s21_decimal value_2 = {{0x739b46c9, 0xc4, 0x0, 0x80040000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x5c122124, 0x262c2f7d, 0x1e58b9, 0x80000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal value_1 = {{0x832c0e40, 0x1daba6, 0x0, 0x80090000}};
  s21_decimal value_2 = {{0xbc7d2cf, 0x1a9d9, 0x0, 0x70000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x8014a3e6, 0x6023c5a, 0x7e59e9bc, 0x800e0000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal value_1 = {{0x5725779, 0x0, 0x0, 0x80060000}};
  s21_decimal value_2 = {{0x3817751d, 0x8c, 0x0, 0x80050000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x33cd35b5, 0xfbb95912, 0x2, 0xb0000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal value_1 = {{0x74b49db5, 0x8689bbf, 0x0, 0x80060000}};
  s21_decimal value_2 = {{0x5ce911de, 0xacd6556b, 0x755e, 0x80160000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xa8be6252, 0xb18719ea, 0x6c834d05, 0xf0000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_6) {
  s21_decimal value_1 = {{0xb40722f9, 0x12, 0x0, 0x20000}};
  s21_decimal value_2 = {{0x4a9d8734, 0x0, 0x0, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xc1996994, 0x738c5938, 0x5, 0x80050000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_7) {
  s21_decimal value_1 = {{0x811a7afe, 0x71a98e77, 0xbf, 0xc0000}};
  s21_decimal value_2 = {{0x36c02379, 0x5d, 0x0, 0x40000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x18634379, 0xbf8d3900, 0x2daf0daf, 0xb0000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_8) {
  s21_decimal value_1 = {{0x47277352, 0xc6e213c0, 0x8, 0x80090000}};
  s21_decimal value_2 = {{0x251deb4f, 0xa, 0x0, 0x70000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x6180d420, 0x498149e6, 0xe3f22e31, 0x800e0000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_9) {
  s21_decimal value_1 = {{0x416a842b, 0x122450d, 0x0, 0x10000}};
  s21_decimal value_2 = {{0x635f40a1, 0xcd77d1e1, 0xa4a, 0x800f0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xc3fe5756, 0x87cb48aa, 0x80500ee0, 0x80050000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_10) {
  s21_decimal value_1 = {{0x46413a01, 0x21da570c, 0x1ccedb3, 0x160000}};
  s21_decimal value_2 = {{0x6ac234d4, 0x74eacf6a, 0x7526, 0x800b0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xc6835dc8, 0x89507d9f, 0x639bc6d7, 0x800b0000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_11) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_mul_12) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000u}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_div_0) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0, 0}};
  s21_decimal value_2 = {{0xffffffff, 0, 0, 0x80000000u}};
  s21_decimal check = {{0x1, 0x1, 0, 0x80000000u}};
  s21_decimal res = {0};

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, s21_is_equal(check, res));
}
END_TEST

START_TEST(s21_div_1) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal value_2 = {{0x5, 0, 0, 0x80000000u}};
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x80000000u}};
  s21_decimal res = {0};

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, s21_is_equal(check, res));
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal value_1 = {{0x56b37c98, 0x6, 0x0, 0x80030000}};
  s21_decimal value_2 = {{0x9c8b7e15, 0x1, 0x0, 0x80070000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xb8412f6f, 0x28c4540b, 0x7f18434a, 0x180000}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal value_1 = {{0xabd3f6ce, 0x4d791546, 0x7b, 0x80020000}};
  s21_decimal value_2 = {{0xec24b4df, 0x1d7dc9c, 0x1b, 0x800a0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xc18b9500, 0x62f9a2f3, 0x938550dd, 0x140000}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000u}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000u}};
  s21_decimal res = {0};

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(3, result);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal value_1 = {{1, 0, 0, 0x80000000u}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  // s21_decimal check = {{5, 0, 0, 0x80010000u}};
  s21_decimal res = {0};
  float res_f = 0.0f;
  float check_f = -0.5f;

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(0, result);
  s21_from_decimal_to_float(res, &res_f);
  ck_assert_float_eq(check_f, res_f);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal value_1 = {{1, 0, 0, 0x80000000u}};
  s21_decimal value_2 = {{4, 0, 0, 0}};
  // s21_decimal check = {{25, 0, 0, 0x80020000u}};
  s21_decimal res = {0};
  float res_f = 0.0f;
  float check_f = -0.25f;

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(0, result);
  s21_from_decimal_to_float(res, &res_f);
  ck_assert_float_eq(check_f, res_f);
}
END_TEST

START_TEST(s21_div_7) {
  s21_decimal value_1 = {{81, 0, 0, 0x80000000u}};
  s21_decimal value_2 = {{8, 0, 0, 0}};
  // s21_decimal check = {{125, 0, 0, 0x80030000u}};
  s21_decimal res = {0};
  float res_f = 0.0f;
  float check_f = -10.125f;

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(0, result);
  s21_from_decimal_to_float(res, &res_f);
  ck_assert_float_eq(check_f, res_f);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal value_1 = {{1, 0, 0, 0x80000000u}};
  s21_decimal value_2 = {{100, 0, 0, 0}};
  // s21_decimal check = {{1, 0, 0, 0x80020000u}};
  s21_decimal res = {0};
  float res_f = 0.0f;
  float check_f = -0.01f;

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(0, result);
  s21_from_decimal_to_float(res, &res_f);
  ck_assert_float_eq(check_f, res_f);
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal value_1 = {{100, 0, 0, 0x80000000u}};
  s21_decimal value_2 = {{4, 0, 0, 0}};
  // s21_decimal check = {{25, 0, 0, 0x80000000u}};
  s21_decimal res = {0};
  float res_f = 0.0f;
  float check_f = -25.0f;

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(0, result);
  s21_from_decimal_to_float(res, &res_f);
  ck_assert_float_eq(check_f, res_f);
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  s21_decimal res = {0};
  float res_f = 0.0f;
  float check_f = 1.0 / 3.0f;

  int result = s21_div(value_1, value_2, &res);
  ck_assert_int_eq(0, result);
  s21_from_decimal_to_float(res, &res_f);
  ck_assert_float_eq(check_f, res_f);
}
END_TEST

START_TEST(s21_div_11) {
  s21_decimal value_1 = {
      {0xae4bdba3, 0x1e135, 0x0, 0x80000}};  // 5290956,50433955
  s21_decimal value_2 = {
      {0x99f17d4f, 0xa7a08, 0x0, 0x60000}};  // 2948927128,173903
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xe1af1cb, 0x3286c7e8, 0xed75c, 0x1c0000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_12) {
  s21_decimal value_1 = {{0x91f995d2, 0x20f3d, 0x0, 0x80010000}};
  s21_decimal value_2 = {{0x4543892d, 0x146803, 0x0, 0x80040000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x699fabad, 0x4215810a, 0x209c6e75, 0x1a0000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_13) {
  s21_decimal value_1 = {{0xce0d7777, 0x1ea5fbc3, 0x0, 0xa0000}};
  s21_decimal value_2 = {{0x1c8c5bb8, 0x7c7, 0x0, 0x80080000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x720b4461, 0x3a0acbef, 0x5371843a, 0x80190000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_14) {
  s21_decimal value_1 = {{0xa5d05e79, 0x116cb495, 0x1cb, 0x800c0000}};
  s21_decimal value_2 = {{0xa609c1b, 0x5b8340ac, 0x176bc81f, 0xe0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xf059ee6c, 0x3a0604b1, 0xf765, 0x801c0000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_15) {
  s21_decimal value_1 = {{0x14ef0a79, 0x4b9ef971, 0x1a8, 0x40000}};
  s21_decimal value_2 = {{0xc94bee48, 0x0, 0x0, 0x80090000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x5fd1ccf5, 0x67702d02, 0x4ae27032, 0x800b0000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_16) {
  s21_decimal value_1 = {{0x3689dec1, 0xde, 0x0, 0x80060000}};
  s21_decimal value_2 = {{0x326e20, 0x0, 0x0, 0x80020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x8a7f1928, 0xb8f86f1b, 0x5d4ee006, 0x1b0000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_17) {
  s21_decimal value_1 = {{0x45a4c994, 0x15, 0x0, 0x10000}};
  s21_decimal value_2 = {{0x5b59c88, 0x0, 0x0, 0x60000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x68749eca, 0xc4ab6e5f, 0x1ed1a5c0, 0x140000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_18) {
  s21_decimal value_1 = {{0x89b41c06, 0x8157a76, 0x0, 0x80010000}};
  s21_decimal value_2 = {{0x9abb1051, 0x397792, 0x0, 0xe0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x2f11bde4, 0x640e5549, 0x745c0d4c, 0x800e0000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_19) {
  s21_decimal value_1 = {{0x61c21cec, 0x42e47582, 0x18180a16, 0x800f0000}};
  s21_decimal value_2 = {{0x297b4b8, 0x0, 0x0, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xce1ed77b, 0xe123afa4, 0x37647fb4, 0x140000}};
  float res_f = 0.0f;
  float check_f = 0.0f;

  int res = s21_div(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &res_f);
  s21_from_decimal_to_float(check, &check_f);
  ck_assert_float_eq(check_f, res_f);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(s21_div_20) {
  s21_decimal value_1 = {{0x115de728, 0x8a7471fe, 0x1c1e7cb, 0x80160000}};
  s21_decimal value_2 = {{0x896678f9, 0x30f00bf2, 0x89a7, 0x800f0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x910c2f11, 0x2bacc072, 0xb12e, 0x1c0000}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_21) {
  s21_decimal value_1 = {{0xb8395498, 0x8a1ad68b, 0x4edb1, 0x80060000}};
  s21_decimal value_2 = {{0xaa100381, 0x36dee755, 0x5e7, 0x80070000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xa57e862d, 0xbbbc5e4f, 0x450f6c99, 0x190000}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_22) {
  s21_decimal value_1 = {{0xb8395498, 0x8a1ad68b, 0x4edb1, 0x80060000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_div_23) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal value_2 = {{0x1, 0, 0, 0x1c0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(s21_div_24) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal value_2 = {{0x1, 0, 0, 0x801c0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(s21_from_int_0) {
  int value = 1;
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, 0}};

  int error_code = s21_from_int_to_decimal(value, &result);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(error_code, 0);
}
END_TEST

START_TEST(s21_from_int_1) {
  int value = 12345;
  s21_decimal result = {0};
  s21_decimal expected = {{12345, 0, 0, 0}};

  int error_code = s21_from_int_to_decimal(value, &result);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(error_code, 0);
}
END_TEST

START_TEST(s21_from_int_2) {
  int value = 0;
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int error_code = s21_from_int_to_decimal(value, &result);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(error_code, 0);
}
END_TEST

START_TEST(s21_from_int_3) {
  int value = -1;
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, INT_MIN}};

  int error_code = s21_from_int_to_decimal(value, &result);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(error_code, 0);
}
END_TEST

START_TEST(s21_from_int_4) {
  int value = -12345;
  s21_decimal result = {0};
  s21_decimal expected = {{12345, 0, 0, INT_MIN}};

  int error_code = s21_from_int_to_decimal(value, &result);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(error_code, 0);
}
END_TEST

START_TEST(s21_from_int_5) {
  int value = INT_MIN;
  s21_decimal result = {0};
  s21_decimal expected = {{INT_MAX + 1u, 0, 0, INT_MIN}};

  int error_code = s21_from_int_to_decimal(value, &result);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(error_code, 0);
}
END_TEST

START_TEST(s21_from_int_6) {
  int value = INT_MAX;
  s21_decimal result = {0};
  s21_decimal expected = {{INT_MAX, 0, 0, 0}};

  int error_code = s21_from_int_to_decimal(value, &result);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(error_code, 0);
}
END_TEST

START_TEST(s21_to_int_0) {
  s21_decimal value = {{1, 0, 0, 0}};
  int result;

  int error_code = s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_to_int_1) {
  s21_decimal value = {{1, 0, 0, INT_MIN}};
  int result;

  int error_code = s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(s21_to_int_2) {
  s21_decimal value = {{1234, 0, 0, 0}};
  int result;

  int error_code = s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, 1234);
}
END_TEST

START_TEST(s21_to_int_3) {
  s21_decimal value = {{1234, 0, 0, 3 << 16}};
  int result = 0;

  int error_code = s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_to_int_4) {
  s21_decimal value = {{1234, 0, 0, (3 << 16) + (INT_MIN)}};
  int result = 0;

  int error_code = s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(s21_to_int_5) {
  s21_decimal value = {{9, 0, 0, 1 << 16}};
  int result = 0;

  int error_code = s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_to_int_6) {
  s21_decimal value = {{9, 0, 0, (1 << 16) + (INT_MIN)}};
  int result = 0;

  int error_code = s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_flt_0) {
  s21_decimal value = {{0, 0, 0, 0}};
  float real = -2.72f;
  // s21_decimal check = {{0x298100, 0x0, 0x0, 0x60000}};
  int return_value = s21_from_float_to_decimal(real, &value);
  float result = 0.0f;
  s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(real, result);
  // ck_assert_int_eq(s21_is_equal(value, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_flt_1) {
  s21_decimal value = {{0, 0, 0, 0}};
  float real = 2.7182818284f;
  // s21_decimal check = {{0x297a4a, 0x0, 0x0, 0x60000}};
  int return_value = s21_from_float_to_decimal(real, &value);
  float result = 0.0f;
  s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(real, result);
  // ck_assert_int_eq(s21_is_equal(value, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_flt_2) {
  s21_decimal value = {{0, 0, 0, 0}};
  float real = 27182818284.f;
  // s21_decimal check = {{0x5438eaa0, 0x6, 0x0, 0x0}};
  int return_value = s21_from_float_to_decimal(real, &value);
  float result = 0.0f;
  s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(real, result);
  // ck_assert_int_eq(s21_is_equal(value, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_flt_3) {
  s21_decimal value = {{0, 0, 0, 0}};
  float real = 1e-28;
  // s21_decimal check = {{0x1, 0x0, 0x0, 0x1c0000}};
  int return_value = s21_from_float_to_decimal(real, &value);
  float result = 0.0f;
  s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(real, result);
  // ck_assert_int_eq(s21_is_equal(value, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_flt_4) {
  s21_decimal value = {{0, 0, 0, 0}};
  float real = 1e+28;
  // s21_decimal check = {{0x31600000, 0x85b549b, 0x204fce28, 0x0}};
  int return_value = s21_from_float_to_decimal(real, &value);
  float result = 0.0f;
  // 9999999442119689768320106496
  // 9999999000000000000000000000
  s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(real, result);
  // ck_assert_int_eq(s21_is_equal(value, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_flt_5) {
  s21_decimal value = {{0, 0, 0, 0}};
  float real = 1e-29;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_from_float_to_decimal(real, &value);
  ck_assert_int_eq(s21_is_equal(value, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_flt_6) {
  s21_decimal value = {{0, 0, 0, 0}};
  float real = 1e+29;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_from_float_to_decimal(real, &value);
  ck_assert_int_eq(s21_is_equal(value, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_flt_7) {
  s21_decimal value = {0};
  float flt = 2.72f;
  float flt_res = 0.0f;
  int result = s21_from_float_to_decimal(flt, &value);
  s21_from_decimal_to_float(value, &flt_res);
  ck_assert_float_eq(flt, flt_res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_flt_8) {
  s21_decimal value = {{0, 0, 0, 0}};
  float real = (-1.0) * 1e-29;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_from_float_to_decimal(real, &value);
  ck_assert_int_eq(s21_is_equal(value, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_flt_9) {
  s21_decimal value = {0};
  float flt = 2.7182818284f;
  float flt_res = 0.0f;
  int result = s21_from_float_to_decimal(flt, &value);
  s21_from_decimal_to_float(value, &flt_res);
  ck_assert_float_eq(flt, flt_res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_to_flt_0) {
  s21_decimal decimal = {{1171617166, 622983331, 0, 589824}};
  float flt = 2.675693E9;
  float flt_res = 0.0f;
  int result = s21_from_decimal_to_float(decimal, &flt_res);
  ck_assert_float_eq(flt, flt_res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_to_flt_1) {
  s21_decimal decimal = {{-1992265181, 1483424946, 0, 458752}};
  float flt = 6.371262E11;
  float flt_res = 0.0f;
  int result = s21_from_decimal_to_float(decimal, &flt_res);
  ck_assert_float_eq(flt, flt_res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_to_flt_2) {
  s21_decimal decimal = {{-1816228279, 1425245217, 0, 1048576}};
  float flt = 612.1382;
  float flt_res = 0.0f;
  int result = s21_from_decimal_to_float(decimal, &flt_res);
  ck_assert_float_eq(flt, flt_res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_to_flt_3) {
  s21_decimal decimal = {{-1390306651, 1614987679, 0, 1376256}};
  float flt = 0.006936319;
  float flt_res = 0.0f;
  int result = s21_from_decimal_to_float(decimal, &flt_res);
  ck_assert_float_eq(flt, flt_res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_to_flt_4) {
  s21_decimal decimal = {{-1872160181, 1133952259, 0, -2147024896}};
  float flt = -4.870288E11;
  float flt_res = 0.0f;
  int result = s21_from_decimal_to_float(decimal, &flt_res);
  ck_assert_float_eq(flt, flt_res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_to_flt_5) {
  s21_decimal decimal = {{0x05555555, 0x14B700CB, 0xAC544CA, 0x1c0000u}};
  float flt = 1.0 / 3.0;
  float flt_res = 0.0f;
  int result = s21_from_decimal_to_float(decimal, &flt_res);
  ck_assert_float_eq(flt, flt_res);
  ck_assert_int_eq(result, 0);
}
END_TEST

// Comparison Functions
START_TEST(s21_is_less_0) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{2, 0, 0, 0}};

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_1) {
  s21_decimal num1 = {{1, 0, 0, 0x80000000}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal num1 = {{1, 0, 0, 0x00010000}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_3) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal num1 = {{2, 0, 0, 0x80000000}};
  s21_decimal num2 = {{1, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_is_less(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_less_6) {
  s21_decimal val1 = {{0, 1, 0x1000, 0x80000000}};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_7) {
  s21_decimal val1 = {{0, 0, 0, 0x80000000}};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {{0, 1, 0x1000, 0x80000000}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_0) {
  s21_decimal num1 = {{3, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal num1 = {{5, 0, 0, 0x80000000}};
  s21_decimal num2 = {{3, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal num1 = {{5, 0, 0, 0x80000000}};
  s21_decimal num2 = {{3, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal num1 = {{1, 0, 0, 0x80000000}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal num1 = {{50, 0, 0, 0x00010000}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {
  s21_decimal num1 = {{0, 0, 0, 0x20000}};
  s21_decimal num2 = {{0, 0, 0, 0x80010000}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_0) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{3, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_1) {
  s21_decimal num1 = {{3, 0, 0, 0x80000000}};
  s21_decimal num2 = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_2) {
  s21_decimal num1 = {{3, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_3) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_greater_4) {
  s21_decimal num1 = {{50, 0, 0, 0x00010000}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_greater_5) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_6) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_7) {
  s21_decimal num1 = {{1, 0, 0, 0x80000000}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_greater_8) {
  s21_decimal val1 = {{0, 1, 0x1000, 0x80000000}};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_9) {
  s21_decimal val1 = {{0, 0, 0, 0x80000000}};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {{0, 1, 0x1000, 0x80000000}};
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_or_equal_0) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{3, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_1) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
  s21_decimal num1 = {{3, 0, 0, 0x80000000}};
  s21_decimal num2 = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
  s21_decimal num1 = {{3, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
  s21_decimal num1 = {{1, 0, 0, 0x80000000}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
  s21_decimal num1 = {{50, 0, 0, 0x00010000}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
  s21_decimal num1 = {{0, 0, 0, 0x80010000}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_equal_0) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_equal_1) {
  s21_decimal num1 = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal num2 = {{5, 0, 0, 0x80000000}};  // -5
  ck_assert_int_eq(s21_is_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal num1 = {{5, 0, 0, 0}};           // 5
  s21_decimal num2 = {{5, 0, 0, 0x80000000}};  // -5
  ck_assert_int_eq(s21_is_equal(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal num1 = {{50, 0, 0, 0x00010000}};  // 5.0
  s21_decimal num2 = {{5, 0, 0, 0}};            // 5
  ck_assert_int_eq(s21_is_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_equal_5) {
  s21_decimal num1 = {{0, 0, 0, 0}};  // 0
  s21_decimal num2 = {{0, 0, 0, 0}};  // 0
  ck_assert_int_eq(s21_is_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_equal_6) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal num2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_equal(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_equal_7) {
  s21_decimal num1 = {{0xfffffffd, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal num2 = {{0x9fffffff, 0x8b21f1b9, 0x3e2129ca, 0x1c0000}};
  ck_assert_int_eq(s21_is_equal(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_not_equal_0) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{3, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_1) {
  s21_decimal num1 = {{5, 0, 0, 0x80000000}};
  s21_decimal num2 = {{3, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal num1 = {{50, 0, 0, 0x00010000}};
  s21_decimal num2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_not_equal_4) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal num2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_5) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 0);
}
END_TEST

START_TEST(s21_is_not_equal_6) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 0);
}
END_TEST

// Other functions
START_TEST(s21_floor_0) {
  s21_decimal value = {{12345, 0, 0, 0x20000}};
  s21_decimal check = {{123, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_1) {
  s21_decimal value = {{12345, 0, 0, 0x80020000u}};
  s21_decimal check = {{124, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  int res = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal value = {{123, 0, 0, 0}};
  s21_decimal check = {{123, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal value = {{123, 0, 0, 0x80000000u}};
  s21_decimal check = {{123, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  int res = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal value = {{12351, 0, 0, 0x20000}};
  s21_decimal check = {{123, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal value = {{12301, 0, 0, 0x80020000u}};
  s21_decimal check = {{124, 0, 0, 0x80000000u}};
  s21_decimal result = {0};
  int res = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_0) {
  s21_decimal value = {{12355, 0, 0, 0x20000}};
  s21_decimal check = {{124, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_round(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal value = {{12345, 0, 0, 0x80010000}};
  s21_decimal check = {{1235, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  int res = s21_round(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal value = {{12501, 0, 0, 0x20000}};
  s21_decimal check = {{125, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_round(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal value = {{12550, 0, 0, 0x80020000}};
  s21_decimal check = {{126, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  int res = s21_round(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal value = {{0, 0, 0, 0x80010000}};
  s21_decimal check = {{0, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  int res = s21_round(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal value = {{1234567, 0, 0, 0x40000}};
  s21_decimal check = {{123, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_round(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal value = {{22354, 0, 0, 0x20000}};
  s21_decimal check = {{224, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_round(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_0) {
  s21_decimal value = {{2235478, 0, 0, 0x40000}};
  s21_decimal check = {{223, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal value = {{2235478, 0, 0, 0x80040000}};
  s21_decimal check = {{223, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal value = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}};
  s21_decimal check = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_negate_0) {
  s21_decimal value = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80060000}};
  s21_decimal check = {{0xffffffff, 0xffffffff, 0xffffffff, 0x60000}};
  s21_decimal result = {0};
  int res = s21_negate(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_negate_1) {
  s21_decimal value = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal check = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal result = {0};
  int res = s21_negate(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal value = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}};
  s21_decimal check = {0};
  s21_decimal result = {0};
  int res = s21_negate(value, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(res, 1);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Test");
  TCase *tc1_1 = tcase_create("Test");
  SRunner *sr = srunner_create(s1);
  int nf = 0;

  suite_add_tcase(s1, tc1_1);

  // Miscellaneous Functions Decimal
  tcase_add_test(tc1_1, get_bit_0);  // get_bit
  tcase_add_test(tc1_1, get_bit_1);
  tcase_add_test(tc1_1, set_bit_0);
  tcase_add_test(tc1_1, set_bit_1);   // set_bit
  tcase_add_test(tc1_1, get_sign_0);  // get_sign
  tcase_add_test(tc1_1, get_sign_1);
  tcase_add_test(tc1_1, set_sign_0);  // set_sign
  tcase_add_test(tc1_1, set_sign_1);
  tcase_add_test(tc1_1, get_scale_0);  // get_scale
  tcase_add_test(tc1_1, get_scale_1);
  tcase_add_test(tc1_1, set_scale_0);  // set_scale
  tcase_add_test(tc1_1, set_scale_1);
  tcase_add_test(tc1_1, is_zero_0);  // is_zero
  tcase_add_test(tc1_1, is_zero_1);
  tcase_add_test(tc1_1, is_zero_2);
  tcase_add_test(tc1_1, is_zero_3);
  tcase_add_test(tc1_1, is_valid_0);  // is_valid
  tcase_add_test(tc1_1, is_valid_1);
  tcase_add_test(tc1_1, is_valid_2);
  tcase_add_test(tc1_1, is_valid_3);
  tcase_add_test(tc1_1, is_valid_4);

  // Miscellaneous Functions Big
  tcase_add_test(tc1_1, get_bit_big_0);  // get_bit_big
  tcase_add_test(tc1_1, get_bit_big_1);
  tcase_add_test(tc1_1, set_bit_big_0);
  tcase_add_test(tc1_1, set_bit_big_1);   // set_bit_big
  tcase_add_test(tc1_1, get_sign_big_0);  // get_sign_big
  tcase_add_test(tc1_1, get_sign_big_1);
  tcase_add_test(tc1_1, set_sign_big_0);  // set_sign_big
  tcase_add_test(tc1_1, set_sign_big_1);
  tcase_add_test(tc1_1, get_scale_big_0);  // get_scale_big
  tcase_add_test(tc1_1, get_scale_big_1);
  tcase_add_test(tc1_1, set_scale_big_0);  // set_scale_big
  tcase_add_test(tc1_1, set_scale_big_1);
  tcase_add_test(tc1_1, is_zero_big_0);  // is_zero_big
  tcase_add_test(tc1_1, is_zero_big_1);
  tcase_add_test(tc1_1, is_zero_big_2);
  tcase_add_test(tc1_1, is_zero_big_3);
  tcase_add_test(tc1_1, first_bit_big_0);  // first_bit
  tcase_add_test(tc1_1, first_bit_big_1);
  tcase_add_test(tc1_1, shift_left_big_0);  // shift_left_big
  tcase_add_test(tc1_1, shift_left_big_1);
  tcase_add_test(tc1_1, shift_left_big_2);
  tcase_add_test(tc1_1, shift_right_big_0);  // shift_right_big
  tcase_add_test(tc1_1, shift_right_big_1);
  tcase_add_test(tc1_1, shift_right_big_2);
  tcase_add_test(tc1_1, big_to_decimal_0);  // s21_from_big_to_decimal
  tcase_add_test(tc1_1, big_to_decimal_1);
  tcase_add_test(tc1_1, big_to_decimal_2);
  tcase_add_test(tc1_1, big_to_decimal_3);
  tcase_add_test(tc1_1, decimal_to_big_0);  // s21_from_decimal_to_big

  // Arithmetic Functions Big
  tcase_add_test(tc1_1, abs_comp_0);  // abs_comp
  tcase_add_test(tc1_1, abs_comp_1);
  tcase_add_test(tc1_1, abs_comp_2);
  tcase_add_test(tc1_1, inc_scale_0);  // inc_scale
  tcase_add_test(tc1_1, inc_scale_1);
  tcase_add_test(tc1_1, inc_scale_2);
  tcase_add_test(tc1_1, inc_scale_3);
  tcase_add_test(tc1_1, dec_scale_0);  // dec_scale
  tcase_add_test(tc1_1, dec_scale_1);
  tcase_add_test(tc1_1, dec_scale_2);
  tcase_add_test(tc1_1, dec_scale_3);
  tcase_add_test(tc1_1, addition_0);  // addition
  tcase_add_test(tc1_1, addition_1);
  tcase_add_test(tc1_1, addition_2);
  tcase_add_test(tc1_1, subtraction_0);  // subtraction
  tcase_add_test(tc1_1, subtraction_1);
  tcase_add_test(tc1_1, subtraction_2);
  tcase_add_test(tc1_1, subtraction_3);
  tcase_add_test(tc1_1, division_0);  // division
  tcase_add_test(tc1_1, division_1);
  tcase_add_test(tc1_1, division_2);

  // Arithmetic Functions Big
  tcase_add_test(tc1_1, s21_add_0);  // s21_add
  tcase_add_test(tc1_1, s21_add_1);
  tcase_add_test(tc1_1, s21_add_2);
  tcase_add_test(tc1_1, s21_add_3);
  tcase_add_test(tc1_1, s21_add_4);
  tcase_add_test(tc1_1, s21_add_5);
  tcase_add_test(tc1_1, s21_add_6);
  tcase_add_test(tc1_1, s21_add_7);
  tcase_add_test(tc1_1, s21_add_8);
  tcase_add_test(tc1_1, s21_add_9);
  tcase_add_test(tc1_1, s21_add_10);
  tcase_add_test(tc1_1, s21_sub_0);  // s21_sub
  tcase_add_test(tc1_1, s21_sub_1);
  tcase_add_test(tc1_1, s21_sub_2);
  tcase_add_test(tc1_1, s21_sub_3);
  tcase_add_test(tc1_1, s21_sub_4);
  tcase_add_test(tc1_1, s21_sub_5);
  tcase_add_test(tc1_1, s21_sub_6);
  tcase_add_test(tc1_1, s21_sub_7);
  tcase_add_test(tc1_1, s21_sub_8);
  tcase_add_test(tc1_1, s21_sub_9);
  tcase_add_test(tc1_1, s21_sub_10);
  tcase_add_test(tc1_1, s21_mul_0);  // s21_mul
  tcase_add_test(tc1_1, s21_mul_1);
  tcase_add_test(tc1_1, s21_mul_2);
  tcase_add_test(tc1_1, s21_mul_3);
  tcase_add_test(tc1_1, s21_mul_4);
  tcase_add_test(tc1_1, s21_mul_5);
  tcase_add_test(tc1_1, s21_mul_6);
  tcase_add_test(tc1_1, s21_mul_7);
  tcase_add_test(tc1_1, s21_mul_8);
  tcase_add_test(tc1_1, s21_mul_9);
  tcase_add_test(tc1_1, s21_mul_10);
  tcase_add_test(tc1_1, s21_mul_11);
  tcase_add_test(tc1_1, s21_mul_12);
  tcase_add_test(tc1_1, s21_div_0);  // s21_div
  tcase_add_test(tc1_1, s21_div_1);
  tcase_add_test(tc1_1, s21_div_2);
  tcase_add_test(tc1_1, s21_div_3);
  tcase_add_test(tc1_1, s21_div_4);
  tcase_add_test(tc1_1, s21_div_5);
  tcase_add_test(tc1_1, s21_div_6);
  tcase_add_test(tc1_1, s21_div_7);
  tcase_add_test(tc1_1, s21_div_8);
  tcase_add_test(tc1_1, s21_div_9);
  tcase_add_test(tc1_1, s21_div_10);
  tcase_add_test(tc1_1, s21_div_11);
  tcase_add_test(tc1_1, s21_div_12);
  tcase_add_test(tc1_1, s21_div_13);
  tcase_add_test(tc1_1, s21_div_14);
  tcase_add_test(tc1_1, s21_div_15);
  tcase_add_test(tc1_1, s21_div_16);
  tcase_add_test(tc1_1, s21_div_17);
  tcase_add_test(tc1_1, s21_div_18);
  tcase_add_test(tc1_1, s21_div_19);
  tcase_add_test(tc1_1, s21_div_20);
  tcase_add_test(tc1_1, s21_div_21);
  tcase_add_test(tc1_1, s21_div_22);
  tcase_add_test(tc1_1, s21_div_23);
  tcase_add_test(tc1_1, s21_div_24);

  // Conversion functions
  tcase_add_test(tc1_1, s21_from_int_0);  // s21_from_int_to_decimal
  tcase_add_test(tc1_1, s21_from_int_1);
  tcase_add_test(tc1_1, s21_from_int_2);
  tcase_add_test(tc1_1, s21_from_int_3);
  tcase_add_test(tc1_1, s21_from_int_4);
  tcase_add_test(tc1_1, s21_from_int_5);
  tcase_add_test(tc1_1, s21_from_int_6);
  tcase_add_test(tc1_1, s21_to_int_0);  // s21_from_decimal_to_int
  tcase_add_test(tc1_1, s21_to_int_1);
  tcase_add_test(tc1_1, s21_to_int_2);
  tcase_add_test(tc1_1, s21_to_int_3);
  tcase_add_test(tc1_1, s21_to_int_4);
  tcase_add_test(tc1_1, s21_to_int_5);
  tcase_add_test(tc1_1, s21_to_int_6);
  tcase_add_test(tc1_1, s21_from_flt_0);  // s21_from_float_to_decimal
  tcase_add_test(tc1_1, s21_from_flt_1);
  tcase_add_test(tc1_1, s21_from_flt_2);
  tcase_add_test(tc1_1, s21_from_flt_3);
  tcase_add_test(tc1_1, s21_from_flt_4);
  tcase_add_test(tc1_1, s21_from_flt_5);
  tcase_add_test(tc1_1, s21_from_flt_6);
  tcase_add_test(tc1_1, s21_from_flt_7);
  tcase_add_test(tc1_1, s21_from_flt_8);
  tcase_add_test(tc1_1, s21_from_flt_9);
  tcase_add_test(tc1_1, s21_to_flt_0);  // s21_from_decimal_to_float
  tcase_add_test(tc1_1, s21_to_flt_1);
  tcase_add_test(tc1_1, s21_to_flt_2);
  tcase_add_test(tc1_1, s21_to_flt_3);
  tcase_add_test(tc1_1, s21_to_flt_4);
  tcase_add_test(tc1_1, s21_to_flt_5);

  // Comparison functions
  tcase_add_test(tc1_1, s21_is_less_0);  // s21_is_less
  tcase_add_test(tc1_1, s21_is_less_1);
  tcase_add_test(tc1_1, s21_is_less_2);
  tcase_add_test(tc1_1, s21_is_less_3);
  tcase_add_test(tc1_1, s21_is_less_4);
  tcase_add_test(tc1_1, s21_is_less_5);
  tcase_add_test(tc1_1, s21_is_less_6);
  tcase_add_test(tc1_1, s21_is_less_7);
  tcase_add_test(tc1_1, s21_is_less_8);
  tcase_add_test(tc1_1, s21_is_less_or_equal_0);  // s21_is_less_or_equal
  tcase_add_test(tc1_1, s21_is_less_or_equal_1);
  tcase_add_test(tc1_1, s21_is_less_or_equal_2);
  tcase_add_test(tc1_1, s21_is_less_or_equal_3);
  tcase_add_test(tc1_1, s21_is_less_or_equal_4);
  tcase_add_test(tc1_1, s21_is_less_or_equal_5);
  tcase_add_test(tc1_1, s21_is_less_or_equal_6);
  tcase_add_test(tc1_1, s21_is_less_or_equal_7);
  tcase_add_test(tc1_1, s21_is_less_or_equal_8);
  tcase_add_test(tc1_1, s21_is_greater_0);  // s21_is_greater
  tcase_add_test(tc1_1, s21_is_greater_1);
  tcase_add_test(tc1_1, s21_is_greater_2);
  tcase_add_test(tc1_1, s21_is_greater_3);
  tcase_add_test(tc1_1, s21_is_greater_4);
  tcase_add_test(tc1_1, s21_is_greater_5);
  tcase_add_test(tc1_1, s21_is_greater_6);
  tcase_add_test(tc1_1, s21_is_greater_7);
  tcase_add_test(tc1_1, s21_is_greater_8);
  tcase_add_test(tc1_1, s21_is_greater_9);
  tcase_add_test(tc1_1, s21_is_greater_10);
  tcase_add_test(tc1_1, s21_is_greater_or_equal_0);  // s21_is_greater_or_equal
  tcase_add_test(tc1_1, s21_is_greater_or_equal_1);
  tcase_add_test(tc1_1, s21_is_greater_or_equal_2);
  tcase_add_test(tc1_1, s21_is_greater_or_equal_3);
  tcase_add_test(tc1_1, s21_is_greater_or_equal_4);
  tcase_add_test(tc1_1, s21_is_greater_or_equal_5);
  tcase_add_test(tc1_1, s21_is_greater_or_equal_6);
  tcase_add_test(tc1_1, s21_is_greater_or_equal_7);
  tcase_add_test(tc1_1, s21_is_equal_0);  // s21_is_equal
  tcase_add_test(tc1_1, s21_is_equal_1);
  tcase_add_test(tc1_1, s21_is_equal_2);
  tcase_add_test(tc1_1, s21_is_equal_3);
  tcase_add_test(tc1_1, s21_is_equal_4);
  tcase_add_test(tc1_1, s21_is_equal_5);
  tcase_add_test(tc1_1, s21_is_equal_6);
  tcase_add_test(tc1_1, s21_is_equal_7);
  tcase_add_test(tc1_1, s21_is_not_equal_0);  // s21_is_not_equal
  tcase_add_test(tc1_1, s21_is_not_equal_1);
  tcase_add_test(tc1_1, s21_is_not_equal_2);
  tcase_add_test(tc1_1, s21_is_not_equal_3);
  tcase_add_test(tc1_1, s21_is_not_equal_4);
  tcase_add_test(tc1_1, s21_is_not_equal_5);
  tcase_add_test(tc1_1, s21_is_not_equal_6);

  // Other functions
  tcase_add_test(tc1_1, s21_floor_0);  // s21_floor
  tcase_add_test(tc1_1, s21_floor_1);
  tcase_add_test(tc1_1, s21_floor_2);
  tcase_add_test(tc1_1, s21_floor_3);
  tcase_add_test(tc1_1, s21_floor_4);
  tcase_add_test(tc1_1, s21_floor_5);
  tcase_add_test(tc1_1, s21_round_0);  // s21_round
  tcase_add_test(tc1_1, s21_round_1);
  tcase_add_test(tc1_1, s21_round_2);
  tcase_add_test(tc1_1, s21_round_3);
  tcase_add_test(tc1_1, s21_round_4);
  tcase_add_test(tc1_1, s21_round_5);
  tcase_add_test(tc1_1, s21_round_6);
  tcase_add_test(tc1_1, s21_truncate_0);  // s21_truncate
  tcase_add_test(tc1_1, s21_truncate_1);
  tcase_add_test(tc1_1, s21_truncate_2);
  tcase_add_test(tc1_1, s21_negate_0);  // s21_negate
  tcase_add_test(tc1_1, s21_negate_1);
  tcase_add_test(tc1_1, s21_negate_2);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  // return nf == 0 ? 0 : 1;
  nf++;
  return 0;
}