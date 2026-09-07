#include "s21_string_test.h"

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_string_h_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

Suite *s21_string_h_suite(void) {
  Suite *s;

  TCase *tc_s21_memchr, *tc_s21_memcmp, *tc_s21_memcpy, *tc_s21_memset,
      *tc_s21_strncat, *tc_s21_strchr, *tc_s21_strncmp, *tc_s21_strncpy,
      *tc_s21_strcspn, *tc_s21_strerror, *tc_s21_strlen, *tc_s21_strpbrk,
      *tc_s21_strrchr, *tc_s21_strstr, *tc_s21_strtok, *tc_s21_sscanf,
      *tc_s21_sprintf, *tc_s21_to_upper, *tc_s21_to_lower, *tc_s21_insert,
      *tc_s21_trim;

  s = suite_create("s21_string_h");

  tc_s21_memchr = tcase_create("s21_memchr");
  tc_s21_memcmp = tcase_create("s21_memcmp");
  tc_s21_memcpy = tcase_create("s21_memcpy");
  tc_s21_memset = tcase_create("s21_memset");
  tc_s21_strncat = tcase_create("s21_strncat");
  tc_s21_strchr = tcase_create("s21_strchr");
  tc_s21_strncmp = tcase_create("s21_strncmp");
  tc_s21_strncpy = tcase_create("s21_strncpy");
  tc_s21_strcspn = tcase_create("s21_strcspn");
  tc_s21_strerror = tcase_create("s21_strerror");
  tc_s21_strlen = tcase_create("s21_strlen");
  tc_s21_strpbrk = tcase_create("s21_strpbrk");
  tc_s21_strrchr = tcase_create("s21_strrchr");
  tc_s21_strstr = tcase_create("s21_strstr");
  tc_s21_strtok = tcase_create("s21_strtok");
  tc_s21_sscanf = tcase_create("s21_sscanf");
  tc_s21_sprintf = tcase_create("s21_sprintf");
  tc_s21_to_upper = tcase_create("s21_to_upper");
  tc_s21_to_lower = tcase_create("s21_to_lower");
  tc_s21_insert = tcase_create("s21_insert");
  tc_s21_trim = tcase_create("s21_trim");

  tcase_add_test(tc_s21_memchr, test_s21_memchr_ch);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_ch_emp);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_inv);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_fl);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_int);

  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_str_match);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_str_nomatch_1);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_str_nomatch_2);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_str_nomatch_3);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_str_null);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_str_short);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_unsigned_match);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_unsigned_nomatch);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_diff_1);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_diff_2);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_str_emp);

  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_ch);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_int);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_same_arr);

  tcase_add_test(tc_s21_memset, test_s21_memset);

  tcase_add_test(tc_s21_strncat, test_s21_strncat);
  tcase_add_test(tc_s21_strchr, test_s21_strchr);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn);
  tcase_add_test(tc_s21_strerror, test_s21_strerror);
  tcase_add_test(tc_s21_strlen, test_s21_strlen);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr);
  tcase_add_test(tc_s21_strstr, test_s21_strstr);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_str);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_delim);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_no_delim);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_empty);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_space);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_null);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_nullsym);
  tcase_add_test(tc_s21_sscanf, test_s21_sscanf);
  tcase_add_test(tc_s21_sprintf, test_s21_sprintf);
  tcase_add_test(tc_s21_to_upper, test_s21_to_upper);
  tcase_add_test(tc_s21_to_lower, test_s21_to_lower);
  tcase_add_test(tc_s21_insert, test_s21_insert);
  tcase_add_test(tc_s21_trim, test_s21_trim);

  suite_add_tcase(s, tc_s21_memchr);
  suite_add_tcase(s, tc_s21_memcmp);
  suite_add_tcase(s, tc_s21_memcpy);
  suite_add_tcase(s, tc_s21_memset);
  suite_add_tcase(s, tc_s21_strncat);
  suite_add_tcase(s, tc_s21_strchr);
  suite_add_tcase(s, tc_s21_strncmp);
  suite_add_tcase(s, tc_s21_strncpy);
  suite_add_tcase(s, tc_s21_strcspn);
  suite_add_tcase(s, tc_s21_strerror);
  suite_add_tcase(s, tc_s21_strlen);
  suite_add_tcase(s, tc_s21_strpbrk);
  suite_add_tcase(s, tc_s21_strrchr);
  suite_add_tcase(s, tc_s21_strstr);
  suite_add_tcase(s, tc_s21_strtok);
  suite_add_tcase(s, tc_s21_sscanf);
  suite_add_tcase(s, tc_s21_sprintf);
  suite_add_tcase(s, tc_s21_to_upper);
  suite_add_tcase(s, tc_s21_to_lower);
  suite_add_tcase(s, tc_s21_insert);
  suite_add_tcase(s, tc_s21_trim);

  return s;
}
