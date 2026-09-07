#include "tests.h"

START_TEST(get_mask_0) {
  figure_t figure = {5, 0, 0, 0x6C00};
  ck_assert_int_eq(get_mask(0, 0, figure), 0);
}
END_TEST

START_TEST(get_mask_1) {
  figure_t figure = {5, 0, 0, 0x6C00};
  ck_assert_int_eq(get_mask(0, 2, figure), 1);
}
END_TEST

START_TEST(get_mask_2) {
  figure_t figure = {5, 0, 0, 0x6C00};
  ck_assert_int_eq(get_mask(1, 1, figure), 1);
}
END_TEST

START_TEST(get_mask_3) {
  figure_t figure = {5, 0, 0, 0x6C00};
  ck_assert_int_eq(get_mask(1, 3, figure), 0);
}
END_TEST

START_TEST(set_mask_0) {
  figure_t figure = {5, 0, 0, 0x6C00};
  set_mask(0, 0, 1, &figure);
  ck_assert_int_eq(figure.mask, 0xEC00);
}
END_TEST

START_TEST(set_mask_1) {
  figure_t figure = {5, 0, 0, 0x6C00};
  set_mask(3, 3, 1, &figure);
  ck_assert_int_eq(figure.mask, 0x6C01);
}
END_TEST

START_TEST(set_mask_2) {
  figure_t figure = {5, 0, 0, 0x6C00};
  set_mask(1, 2, 1, &figure);
  ck_assert_int_eq(figure.mask, 0x6E00);
}
END_TEST

START_TEST(set_mask_3) {
  figure_t figure = {5, 0, 0, 0xF000};
  set_mask(0, 0, 0, &figure);
  ck_assert_int_eq(figure.mask, 0x7000);
}
END_TEST

START_TEST(set_mask_4) {
  figure_t figure = {5, 0, 0, 0x6F00};
  set_mask(1, 2, 0, &figure);
  ck_assert_int_eq(figure.mask, 0x6D00);
}
END_TEST

START_TEST(set_mask_5) {
  figure_t figure = {5, 0, 0, 0x6C01};
  set_mask(3, 3, 0, &figure);
  ck_assert_int_eq(figure.mask, 0x6C00);
}
END_TEST

START_TEST(cut_mask_0) {
  figure_t figure = {5, 0, 0, 0x6C01};
  cut_mask(1, &figure);
  ck_assert_int_eq(figure.mask, 0x0601);
}
END_TEST

START_TEST(cut_mask_1) {
  figure_t figure = {5, 0, 0, 0x4444};
  cut_mask(0, &figure);
  ck_assert_int_eq(figure.mask, 0x0444);
}
END_TEST

START_TEST(cut_mask_2) {
  figure_t figure = {5, 0, 0, 0x8421};
  cut_mask(0, &figure);
  ck_assert_int_eq(figure.mask, 0x0421);
}
END_TEST

START_TEST(cut_mask_3) {
  figure_t figure = {5, 0, 0, 0x8421};
  cut_mask(3, &figure);
  ck_assert_int_eq(figure.mask, 0x0842);
}
END_TEST

Suite *mask_tests(void) {
  Suite *s = suite_create("FIGURE MASK TESTS");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, get_mask_0);
  tcase_add_test(tc_core, get_mask_1);
  tcase_add_test(tc_core, get_mask_2);
  tcase_add_test(tc_core, get_mask_3);

  tcase_add_test(tc_core, set_mask_0);
  tcase_add_test(tc_core, set_mask_1);
  tcase_add_test(tc_core, set_mask_2);
  tcase_add_test(tc_core, set_mask_3);
  tcase_add_test(tc_core, set_mask_4);
  tcase_add_test(tc_core, set_mask_5);

  tcase_add_test(tc_core, cut_mask_0);
  tcase_add_test(tc_core, cut_mask_1);
  tcase_add_test(tc_core, cut_mask_2);
  tcase_add_test(tc_core, cut_mask_3);

  suite_add_tcase(s, tc_core);
  return s;
}