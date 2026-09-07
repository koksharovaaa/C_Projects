#ifndef S21_STRING_TEST_H
#define S21_STRING_TEST_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define FLOAT_CMP(a, b, epsilon)                                       \
  ((sizeof(a) == sizeof(float))         ? fabsf((a) - (b)) < (epsilon) \
   : (sizeof(a) == sizeof(long double)) ? fabsl((a) - (b)) < (epsilon) \
                                        : fabs((a) - (b)) < (epsilon))

#define TESTED_STRINGS                                                       \
  "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n\0", "\0", \
      "Hello World!", "o W", "String", "S", "St", "ing", "g", "", "\0",      \
      "\0\0\0", "\n", "\r", "\t", "\b", "\f", "\v"

Suite *s21_string_h_suite(void);

START_TEST(test_s21_memchr_ch) {
  const size_t n_max = 12;
  unsigned char test_str[][12] = {
      "Hello world\0", " \n\0", "Hello World!", "g", "", "\0\0\0", "123\0 456"};
  for (size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    for (int c = 0; c < 128; c++)
      for (size_t n = 0; n <= n_max; n++)
        ck_assert_ptr_eq(s21_memchr(test_str[i], c, n),
                         memchr(test_str[i], c, n));
  }
}
END_TEST

START_TEST(test_s21_memchr_ch_emp) {
  char test_str[] = "";
  size_t n_max = 2;
  int c = 'A';

  for (size_t n = 0; n <= n_max; n++)
    ck_assert_ptr_eq(s21_memchr(test_str, c, n), memchr(test_str, c, n));
}
END_TEST

START_TEST(test_s21_memchr_inv) {
  const char test_str[] = "Hello!";
  size_t n = strlen(test_str);
  int c = 299;

  ck_assert_ptr_eq(s21_memchr(test_str, c, n), memchr(test_str, c, n));
}
END_TEST

START_TEST(test_s21_memchr_fl) {
  float test[] = {1.01, -1.00000001, -0.000000001, 2000, 3.14, 8999.9999, -7};
  for (int c = 0; c < 128; c++)
    for (size_t n = 0; n <= sizeof(test); n++)
      ck_assert_ptr_eq(s21_memchr(test, c, n), memchr(test, c, n));
}
END_TEST

START_TEST(test_s21_memchr_int) {
  int test[] = {1, 2, 4, 1000, -1, 64};
  for (int c = 0; c < 128; c++)
    for (size_t n = 0; n <= sizeof(test); n++)
      ck_assert_ptr_eq(s21_memchr(test, c, n), memchr(test, c, n));
}
END_TEST

START_TEST(test_s21_memcmp_str_match) {
  const char str_1[] = "Hello world!";
  const char str_2[] = "Hello world!";
  size_t n_max = sizeof(str_1);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_str_nomatch_1) {
  const char str_1[] = "1Hello world!";
  const char str_2[] = "2Hello world!";
  size_t n_max = sizeof(str_1);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_str_nomatch_2) {
  const char str_1[] = "Hello1world!";
  const char str_2[] = "Hello2world!";
  size_t n_max = sizeof(str_1);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_str_nomatch_3) {
  const char str_1[] = "Hello world!1";
  const char str_2[] = "Hello world!2";
  size_t n_max = sizeof(str_1);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_str_null) {
  const char str_1[] = "Hello\0World";
  const char str_2[] = "Hello\0Hello";
  size_t n_max = sizeof(str_1);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_str_short) {
  const char str_1[] = "Hello";
  const char str_2[] = "Hello world!";
  size_t n_max = sizeof(str_2);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_unsigned_match) {
  const unsigned char str_1[] = {1, 2, 3, 4, 5};
  const unsigned char str_2[] = {1, 2, 3, 4, 5};
  size_t n_max = sizeof(str_1);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_unsigned_nomatch) {
  const unsigned char str_1[] = {1, 2, 3, 4, 5};
  const unsigned char str_2[] = {1, 2, 0, 4, 5};
  size_t n_max = sizeof(str_1);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_diff_1) {
  const int str_1[] = {0, 1, 2, -3, 4, 5, 70};
  const float str_2[] = {0, 1.0, 2.0, 3.0, 4.0, 5.0, 70.789};
  size_t n_max = sizeof(str_1);
  for (size_t n = 0; n <= n_max; n++)
    ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_s21_memcmp_diff_2) {
  const int test_ints[] = {1, 2, 4, 1000, -1, 64};
  const unsigned char test_char[] = "ABCDEFGHIJKLMNO";
  size_t n = sizeof(test_char);
  ck_assert_int_eq(s21_memcmp(test_char, test_ints, n),
                   memcmp(test_char, test_ints, n));
}
END_TEST

START_TEST(test_s21_memcmp_str_emp) {
  const char test_str_1[] = "";
  const char test_str_2[] = "";
  size_t n = 1;
  ck_assert_int_eq(s21_memcmp(test_str_1, test_str_2, n),
                   memcmp(test_str_1, test_str_2, n));
}
END_TEST

START_TEST(test_s21_memcpy_ch) {
  unsigned char test_str[][12] = {
      "Hello world\0", " \n\0", "Hello World!", "g", "", "\0\0\0", "123\0 456"};
  unsigned char s_1[] = "ABCDEFGHIJKLMNO";
  unsigned char s_2[] = "ABCDEFGHIJKLMNO";
  size_t n_max = 12;
  for (size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    for (size_t n = 0; n <= n_max; n++) {
      ck_assert_str_eq(s21_memcpy(s_1, test_str[i], n),
                       memcpy(s_2, test_str[i], n));
      ck_assert_mem_eq(s_1, s_2, sizeof(s_1));
    }
  }
}
END_TEST

START_TEST(test_s21_memcpy_int) {
  int source[] = {1, 2, 4, 1000, -1, 64};
  int test_1[6] = {0};
  int test_2[6] = {0};

  s21_memcpy(test_1, source, sizeof(source));
  memcpy(test_2, source, sizeof(source));
  ck_assert_mem_eq(test_1, test_2, sizeof(source));
}
END_TEST

START_TEST(test_s21_memcpy_same_arr) {
  unsigned char s_1[] = "ABCDEFGHIJKLMNO";
  unsigned char s_2[] = "ABCDEFGHIJKLMNO";
  size_t n = 5;
  ck_assert_str_eq(s21_memcpy(s_1, s_1 + n + 1, n),
                   memcpy(s_2, s_2 + n + 1, n));
  ck_assert_mem_eq(s_1, s_2, sizeof(s_1));
}
END_TEST

START_TEST(test_s21_memset) {
  unsigned char test_1[][12] = {
      "Hello world\0", " \n\0", "Hello World!", "g", "", "\0\0\0", "123\0 456"};
  unsigned char test_2[][12] = {
      "Hello world\0", " \n\0", "Hello World!", "g", "", "\0\0\0", "123\0 456"};
  size_t n_max = sizeof(test_1[0]);
  for (size_t i = 0; i < sizeof(test_1) / sizeof(test_1[0]); i++) {
    for (int c = 0; c < 128; c++)
      for (size_t n = 0; n <= n_max; n++)
        ck_assert_mem_eq(s21_memset(test_1[i], c, n), memset(test_2[i], c, n),
                         n);
  }
}
END_TEST

START_TEST(test_s21_strncat) {
  char *tested_strings[] = {TESTED_STRINGS};
  char s_1[256] = "\0";
  char s_2[256] = "\0";
  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++) {
    size_t n = strlen(tested_strings[i]);
    ck_assert_str_eq(s21_strncat(s_1, tested_strings[i], n),
                     strncat(s_2, tested_strings[i], n));
  }
}
END_TEST

START_TEST(test_s21_strchr) {
  char *tested_strings[] = {TESTED_STRINGS};
  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++)
    for (int c = 0; c < 128; c++)
      if (strchr(tested_strings[i], c))
        ck_assert_str_eq(s21_strchr(tested_strings[i], c),
                         strchr(tested_strings[i], c));
      else {
        ck_assert_int_eq(s21_strchr(tested_strings[i], c) == NULL,
                         strchr(tested_strings[i], c) == NULL);
      }
}
END_TEST

START_TEST(test_s21_strncmp) {
  char *tested_strings[] = {TESTED_STRINGS};
  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++)
    for (size_t j = 0; j < sizeof(tested_strings) / sizeof(tested_strings[0]);
         j++) {
      size_t n_max = s21_strlen(tested_strings[j]) + 1;
      for (size_t n = 0; n <= n_max; n++)
        ck_assert_int_eq(
            s21_strncmp(tested_strings[i], tested_strings[j], n) > 0,
            strncmp(tested_strings[i], tested_strings[j], n) > 0);
    }
}
END_TEST

START_TEST(test_s21_strncpy) {
  char tested_strings[][13] = {
      "Hello world\0", " \n\0", "Hello World!", "g", "", "\0\0\0", "123456"};
  size_t n_max = 13;
  char s_1[128] = "\0";
  char s_2[128] = "\0";
  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++)
    for (size_t n = 0; n < n_max; n++)
      ck_assert_str_eq(s21_strncpy(s_1, tested_strings[i], n),
                       strncpy(s_2, tested_strings[i], n));
}
END_TEST

START_TEST(test_s21_strcspn) {
  char *tested_strings[] = {TESTED_STRINGS};
  char *delimiters[] = {"aeiou", "xyz", "123", " ", "\n", "\0"};

  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++) {
    for (size_t j = 0; j < sizeof(delimiters) / sizeof(delimiters[0]); j++) {
      size_t expected = strcspn(tested_strings[i], delimiters[j]);
      size_t actual = s21_strcspn(tested_strings[i], delimiters[j]);
      ck_assert_int_eq(actual, expected);
    }
  }
}
END_TEST

START_TEST(test_s21_strerror) {
  ck_assert_str_eq(s21_strerror(0), "Success");
  ck_assert_str_eq(s21_strerror(1), "Operation not permitted");
  ck_assert_str_eq(s21_strerror(2), "No such file or directory");
  ck_assert_str_eq(s21_strerror(3), "No such process");
  ck_assert_str_eq(s21_strerror(4), "Interrupted system call");
  ck_assert_str_eq(s21_strerror(5), "Input/output error");

  ck_assert_str_eq(s21_strerror(-1), "Unknown error -1");
  ck_assert_str_eq(s21_strerror(1000), "Unknown error 1000");
}
END_TEST

START_TEST(test_s21_strlen) {
  char *tested_strings[] = {TESTED_STRINGS};

  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++)
    ck_assert_int_eq(s21_strlen(tested_strings[i]), strlen(tested_strings[i]));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char *tested_strings[] = {TESTED_STRINGS};
  char *tested_delimiters[] = {"aeiou", "xyz", "123", " ", "\n", "\0"};

  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++) {
    for (size_t j = 0;
         j < sizeof(tested_delimiters) / sizeof(tested_delimiters[0]); j++) {
      char *expected = strpbrk(tested_strings[i], tested_delimiters[j]);
      char *actual = s21_strpbrk(tested_strings[i], tested_delimiters[j]);

      if (expected) {
        ck_assert_str_eq(actual, expected);
      } else {
        ck_assert_ptr_null(actual);
      }
    }
  }
}
END_TEST

START_TEST(test_s21_strrchr) {
  char *tested_strings[] = {TESTED_STRINGS};

  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++)
    for (int c = 0; c < 128; c++)
      if (strrchr(tested_strings[i], c))
        ck_assert_str_eq(s21_strrchr(tested_strings[i], c),
                         strrchr(tested_strings[i], c));
      else {
        ck_assert_int_eq(s21_strrchr(tested_strings[i], c) == NULL,
                         strrchr(tested_strings[i], c) == NULL);
      }
}
END_TEST

START_TEST(test_s21_strstr) {
  char *tested_strings[] = {TESTED_STRINGS};

  for (size_t i = 0; i < sizeof(tested_strings) / sizeof(tested_strings[0]);
       i++)
    for (size_t j = 0; j < sizeof(tested_strings) / sizeof(tested_strings[0]);
         j++) {
      char *expected = strstr(tested_strings[i], tested_strings[j]);
      char *actual = s21_strstr(tested_strings[i], tested_strings[j]);

      if (expected) {
        ck_assert_str_eq(actual, expected);
      } else {
        ck_assert_ptr_null(actual);
      }
    }
}
END_TEST

START_TEST(test_s21_strtok_str) {
  char str_1_1[] = "Hello, world!";
  char str_1_2[] = "Hello, world!";
  const char *d_1 = " ,!";
  char *test_1 = s21_strtok(str_1_1, d_1);
  char *test_2 = strtok(str_1_2, d_1);
  while (test_1 && test_2) {
    ck_assert_str_eq(test_1, test_2);
    test_1 = s21_strtok(s21_NULL, d_1);
    test_2 = strtok(s21_NULL, d_1);
  }
  ck_assert_ptr_eq(test_1, test_2);
}
END_TEST

START_TEST(test_s21_strtok_delim) {
  char str_2[] = "!!!!!!!!";
  const char *d_2 = "!";
  ck_assert_ptr_eq(s21_strtok(str_2, d_2), strtok(str_2, d_2));
}
END_TEST

START_TEST(test_s21_strtok_no_delim) {
  char str_3[] = "helloworld";
  const char *d_3 = ",";
  ck_assert_str_eq(s21_strtok(str_3, d_3), strtok(str_3, d_3));
}
END_TEST

START_TEST(test_s21_strtok_empty) {
  char str_4[] = "";
  const char *d_4 = " ,!";
  ck_assert_ptr_eq(s21_strtok(str_4, d_4), strtok(str_4, d_4));
}
END_TEST

START_TEST(test_s21_strtok_space) {
  char str_5_1[] = "Hello world hello world ";
  char str_5_2[] = "Hello world hello world ";
  const char *d_5 = " ";
  char *test_1 = s21_strtok(str_5_1, d_5);
  char *test_2 = strtok(str_5_2, d_5);
  while (test_1 && test_2) {
    ck_assert_str_eq(test_1, test_2);
    test_1 = s21_strtok(s21_NULL, d_5);
    test_2 = strtok(s21_NULL, d_5);
  }
  ck_assert_ptr_eq(test_1, test_2);
}
END_TEST

START_TEST(test_s21_strtok_null) {
  char *str_6 = NULL;
  const char *d_6 = " ,!";
  ck_assert_ptr_eq(s21_strtok(str_6, d_6), NULL);
}
END_TEST

START_TEST(test_s21_strtok_nullsym) {
  char str_7[] = "\0\0\0";
  const char *d_7 = "\0";
  ck_assert_ptr_eq(s21_strtok(str_7, d_7), strtok(str_7, d_7));
}
END_TEST

START_TEST(test_s21_sscanf) {
  const char *input;
  int s21_int, std_int, s21_n, std_n;
  short int s21_sint, std_sint;
  long int s21_lint, std_lint;
  float s21_float, std_float;
  double s21_double, std_double;
  long double s21_ldouble, std_ldouble;
  unsigned int s21_uint, std_uint;
  unsigned int s21_oct, std_oct;
  unsigned int s21_hex1, std_hex1, s21_hex2, std_hex2;
  char s21_char, std_char;
  char s21_str[10], std_str[10];
  void *s21_ptr = NULL, *std_ptr = NULL;

  // 1. Тест целых чисел (d, i)
  input = "+2147483647 -2147483648";
  s21_sscanf(input, "%d %i", &s21_int, &s21_int);
  sscanf(input, "%d %i", &std_int, &std_int);
  ck_assert_int_eq(s21_int, std_int);

  // 2. Тест строк
  input = "Hello World";
  s21_sscanf(input, "%s %s", s21_str, s21_str);
  sscanf(input, "%9s %9s", std_str, std_str);
  ck_assert_str_eq(s21_str, std_str);

  // 3. Тест шестнадцатеричных чисел (x, X)
  input = "FFFFFFFF 0";
  s21_sscanf(input, "%x %X", &s21_hex1, &s21_hex2);
  sscanf(input, "%x %X", &std_hex1, &std_hex2);
  ck_assert_int_eq(s21_hex1, std_hex1);
  ck_assert_int_eq(s21_hex2, std_hex2);

  // 4. Тест восьмеричных чисел (o)
  input = "17777777777 0";
  s21_sscanf(input, "%o %o", &s21_oct, &s21_oct);
  sscanf(input, "%o %o", &std_oct, &std_oct);
  ck_assert_int_eq(s21_oct, std_oct);

  // 5. Тест чисел с плавающей точкой (f, g, G, e, E)
  input = "+3.14159 1e10";
  s21_sscanf(input, "%f %f %f", &s21_float, &s21_float, &s21_float);
  sscanf(input, "%f %f %f", &std_float, &std_float, &std_float);
  ck_assert(FLOAT_CMP(s21_float, std_float, 1e-6));

  input = "2.718281828459045 -1.0e-10 1.234567890123456789E+308";
  s21_sscanf(input, "%lf %lf %Lf", &s21_double, &s21_double, &s21_ldouble);
  sscanf(input, "%lf %lf %Lf", &std_double, &std_double, &std_ldouble);
  ck_assert(FLOAT_CMP(s21_double, std_double, 1e-6));
  ck_assert(FLOAT_CMP(s21_ldouble, std_ldouble, 1e-6));

  input = "3.14159 -2.71 1e10";
  s21_sscanf(input, "%g %G %e", &s21_float, &s21_float, &s21_float);
  sscanf(input, "%g %G %e", &std_float, &std_float, &std_float);
  ck_assert(FLOAT_CMP(s21_float, std_float, 1e-6));

  input = "3.402823466e+38 1.401298464e-45 -1.175494351e-38";
  s21_sscanf(input, "%E %G %g", &s21_float, &s21_float, &s21_float);
  sscanf(input, "%E %G %g", &std_float, &std_float, &std_float);
  ck_assert(FLOAT_CMP(s21_float, std_float, 1e-6));

  // 6. Тест символов (h)
  input = "A B";
  s21_sscanf(input, "%c %c", &s21_char, &s21_char);
  sscanf(input, "%c %c", &std_char, &std_char);
  ck_assert_int_eq(s21_char, std_char);

  // 7. Тест указателя (p)
  input = "0x7ffec0ff0b30";
  s21_sscanf(input, "%p %p", &s21_ptr, &s21_ptr);
  sscanf(input, "%p %p", &std_ptr, &std_ptr);
  ck_assert_ptr_eq(s21_ptr, std_ptr);

  // 8. Тест беззнаковых целых чисел (u)
  input = "4294967295 0";
  s21_sscanf(input, "%u %u", &s21_uint, &s21_uint);
  sscanf(input, "%u %u", &std_uint, &std_uint);
  ck_assert_int_eq(s21_uint, std_uint);

  // 9. Тест ширины
  input = "123456789";
  s21_sscanf(input, "%3d %5d", &s21_int, &s21_int);
  sscanf(input, "%3d %5d", &std_int, &std_int);
  ck_assert_int_eq(s21_int, std_int);

  // 10. Тест знака процента (%)
  input = "%";
  int s21_ret = s21_sscanf(input, "%% %%");
  int std_ret = sscanf(input, "%% %%");
  ck_assert_int_eq(s21_ret, std_ret);

  // 11. Тест спецификатора %n
  input = "12345 67890";
  s21_sscanf(input, "%d %n", &s21_int, &s21_n);
  sscanf(input, "%d %n", &std_int, &std_n);
  ck_assert_int_eq(s21_int, std_int);
  ck_assert_int_eq(s21_n, std_n);

  // 12. Тест длины
  input = "123 123348448484";
  s21_sscanf(input, "%hd %ld", &s21_sint, &s21_lint);
  sscanf(input, "%hd %ld", &std_sint, &std_lint);
  ck_assert_int_eq(s21_sint, std_sint);
  ck_assert_int_eq(s21_lint, std_lint);

  // 13. Тест *
  input = "12345 67890";
  s21_sscanf(input, "%*d %d", &s21_int);
  sscanf(input, "%*d %d", &std_int);
  ck_assert_int_eq(s21_int, std_int);
}
END_TEST

START_TEST(test_s21_sprintf) {
  char *tested_strings[] = {TESTED_STRINGS};
  char buffer1[4096] = {0}, buffer2[4096] = {0}, format_string[4096],
       buffer_format_string[128] = {0}, width_s[10] = {0},
       precision_s[10] = {0}, buffer_for_1ch[2] = {0};
  int result1 = 0, result2 = 0;

  const char *flags = "-+ 0#";
  const char *specifiers = "udc%sfoxXeEp";

  strcpy(format_string, "%ls\n");
  result1 = s21_sprintf(buffer1, format_string, L"wide string");
  result2 = sprintf(buffer2, format_string, L"wide string");
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%lc\n");
  result1 = s21_sprintf(buffer1, format_string, L'w');
  result2 = sprintf(buffer2, format_string, L'w');
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%d\n");
  result1 = s21_sprintf(buffer1, format_string, 0);
  result2 = sprintf(buffer2, format_string, 0);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%u\n");
  result1 = s21_sprintf(buffer1, format_string, 0u);
  result2 = sprintf(buffer2, format_string, 0u);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%g\n");
  result1 = s21_sprintf(buffer1, format_string, 0.10000);
  result2 = sprintf(buffer2, format_string, 0.10000);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%.2g\n");
  result1 = s21_sprintf(buffer1, format_string, 100.00000);
  result2 = sprintf(buffer2, format_string, 100.00000);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%.2G\n");
  result1 = s21_sprintf(buffer1, format_string, 100.00000);
  result2 = sprintf(buffer2, format_string, 100.00000);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%.0G\n");
  result1 = s21_sprintf(buffer1, format_string, 0.99);
  result2 = sprintf(buffer2, format_string, 0.99);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%.1G\n");
  result1 = s21_sprintf(buffer1, format_string, 0.0000000099);
  result2 = sprintf(buffer2, format_string, 0.0000000099);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%.0G\n");
  result1 = s21_sprintf(buffer1, format_string, 9.9);
  result2 = sprintf(buffer2, format_string, 9.9);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%*.*Lf");
  long double d = 7777777777777777.923456789012345678901234567890L;
  result1 = s21_sprintf(buffer1, format_string, 120, 15, d);
  result2 = sprintf(buffer2, format_string, 120, 15, d);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%hd-%hd-%hd\n");
  result1 = s21_sprintf(buffer1, format_string, SHRT_MIN, 0, SHRT_MAX);
  result2 = sprintf(buffer2, format_string, SHRT_MIN, 0, SHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%d-%d-%d\n");
  result1 = s21_sprintf(buffer1, format_string, INT_MIN, 0, INT_MAX);
  result2 = sprintf(buffer2, format_string, INT_MIN, 0, INT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%ld-%ld-%ld\n");
  result1 = s21_sprintf(buffer1, format_string, LONG_MIN, 0, LONG_MAX);
  result2 = sprintf(buffer2, format_string, LONG_MIN, 0, LONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%hu-%hu-%hu\n");
  result1 = s21_sprintf(buffer1, format_string, USHRT_MAX, 0, SHRT_MAX);
  result2 = sprintf(buffer2, format_string, USHRT_MAX, 0, SHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%u-%u-%u\n");
  result1 = s21_sprintf(buffer1, format_string, UINT_MAX, 0, INT_MAX);
  result2 = sprintf(buffer2, format_string, UINT_MAX, 0, INT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%lu-%lu-%lu\n");
  result1 = s21_sprintf(buffer1, format_string, ULONG_MAX, 0, LONG_MAX);
  result2 = sprintf(buffer2, format_string, ULONG_MAX, 0, LONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%hx-%hx-%hx\n");
  result1 = s21_sprintf(buffer1, format_string, USHRT_MAX, 0, SHRT_MAX);
  result2 = sprintf(buffer2, format_string, USHRT_MAX, 0, SHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%x-%x-%x\n");
  result1 = s21_sprintf(buffer1, format_string, UINT_MAX, 0, INT_MAX);
  result2 = sprintf(buffer2, format_string, UINT_MAX, 0, INT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%lx-%lx-%lx\n");
  result1 = s21_sprintf(buffer1, format_string, ULONG_MAX, 0, LONG_MAX);
  result2 = sprintf(buffer2, format_string, ULONG_MAX, 0, LONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%ho-%ho-%ho\n");
  result1 = s21_sprintf(buffer1, format_string, USHRT_MAX, 0, SHRT_MAX);
  result2 = sprintf(buffer2, format_string, USHRT_MAX, 0, SHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%o-%o-%o\n");
  result1 = s21_sprintf(buffer1, format_string, UINT_MAX, 0, INT_MAX);
  result2 = sprintf(buffer2, format_string, UINT_MAX, 0, INT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%lo-%lo-%lo\n");
  result1 = s21_sprintf(buffer1, format_string, ULONG_MAX, 0, LONG_MAX);
  result2 = sprintf(buffer2, format_string, ULONG_MAX, 0, LONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%hX-%hX-%hX\n");
  result1 = s21_sprintf(buffer1, format_string, USHRT_MAX, 0, SHRT_MAX);
  result2 = sprintf(buffer2, format_string, USHRT_MAX, 0, SHRT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%X-%X-%X\n");
  result1 = s21_sprintf(buffer1, format_string, UINT_MAX, 0, INT_MAX);
  result2 = sprintf(buffer2, format_string, UINT_MAX, 0, INT_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%lX-%lX-%lX\n");
  result1 = s21_sprintf(buffer1, format_string, ULONG_MAX, 0, LONG_MAX);
  result2 = sprintf(buffer2, format_string, ULONG_MAX, 0, LONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  strcpy(format_string, "%p-%p-%p\n");
  // result1 = s21_sprintf(buffer1, format_string, ULONG_MAX, 0, LONG_MAX);
  // result2 = sprintf(buffer2, format_string, ULONG_MAX, 0, LONG_MAX);
  result1 = s21_sprintf(buffer1, format_string, ULONG_MAX, 1, LONG_MAX);
  result2 = sprintf(buffer2, format_string, ULONG_MAX, 1, LONG_MAX);
  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);

  for (size_t f1 = 0; f1 <= strlen(flags); f1++)
    for (int width = -2; width < 32; width += 16)
      for (int precision = -2; precision < 9; precision += 2)
        for (size_t s = 0; s < strlen(specifiers); s++) {
          strcpy(buffer_format_string, "___%");

          if (f1 < strlen(flags) && specifiers[s] != 's' &&
              specifiers[s] != 'c') {
            buffer_for_1ch[0] = flags[f1];
            strcat(buffer_format_string, buffer_for_1ch);
          }

          if (width > -1) {
            sprintf(width_s, "%d", width);
            strcat(buffer_format_string, width_s);
          }

          if (precision > -1) {
            sprintf(precision_s, "%d", precision);
            strcat(buffer_format_string, ".");
            strcat(buffer_format_string, precision_s);
          }

          buffer_for_1ch[0] = specifiers[s];
          strcat(buffer_format_string, buffer_for_1ch);
          strcat(buffer_format_string, "___");

          strcpy(format_string, buffer_format_string);
          strcat(format_string, buffer_format_string);
          strcat(format_string, buffer_format_string);
          strcat(format_string, buffer_format_string);
          strcat(format_string, buffer_format_string);

          // removed c, %, p specifiers
          if (specifiers[s] == 'd' || specifiers[s] == 'u' ||
              specifiers[s] == 'o' || specifiers[s] == 'x' ||
              specifiers[s] == 'X') {
            result1 = s21_sprintf(buffer1, format_string, 0, 16, 32, 64, 127);
            result2 = sprintf(buffer2, format_string, 0, 16, 32, 64, 127);
            ck_assert_str_eq(buffer1, buffer2);
            ck_assert_int_eq(result1, result2);
          }

          if (specifiers[s] == 's') {
            for (size_t t = 1;
                 t < sizeof(tested_strings) / sizeof(tested_strings[0]); t++) {
              result1 = s21_sprintf(buffer1, format_string, tested_strings[t],
                                    tested_strings[t - 1], tested_strings[t],
                                    tested_strings[t - 1], "END");
              result2 = sprintf(buffer2, format_string, tested_strings[t],
                                tested_strings[t - 1], tested_strings[t],
                                tested_strings[t - 1], "END");

              ck_assert_str_eq(buffer1, buffer2);
              ck_assert_int_eq(result1, result2);
            }
          }

          if (specifiers[s] == 'c') {
            result1 = s21_sprintf(buffer1, format_string, 0, 16, 32, 64, 127);
            result2 = sprintf(buffer2, format_string, 0, 16, 32, 64, 127);
            ck_assert_str_eq(buffer1, buffer2);
            ck_assert_int_eq(result1, result2);
          }

          if (specifiers[s] == 'f' || specifiers[s] == 'e' ||
              specifiers[s] == 'E' || specifiers[s] == 'g' ||
              specifiers[s] == 'G') {
            double d1 = 0.0001;
            double d2 = pow(10, precision % 20) + 0.1;
            double d3 = 0.000;

            result1 = s21_sprintf(buffer1, format_string, d3, d1, -d1, d2, -d2);
            result2 = sprintf(buffer2, format_string, d3, d1, -d1, d2, -d2);

            ck_assert_str_eq(buffer1, buffer2);
            ck_assert_int_eq(result1, result2);
          }
        }
}
END_TEST

START_TEST(test_s21_to_upper) {
  const char *input = "hello";
  char *result = s21_to_upper(input);
  ck_assert_str_eq(result, "HELLO");
  free(result);

  input = "";
  result = s21_to_upper(input);
  ck_assert_str_eq(result, "");
  free(result);

  input = NULL;
  result = s21_to_upper(input);
  ck_assert_ptr_eq(result, NULL);

  input = "HELLO";
  result = s21_to_upper(input);
  ck_assert_str_eq(result, "HELLO");
  free(result);

  input = "hello, world!";
  result = s21_to_upper(input);
  ck_assert_str_eq(result, "HELLO, WORLD!");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower) {
  const char *input = "HELLO";
  char *result = s21_to_lower(input);
  ck_assert_str_eq(result, "hello");
  free(result);

  input = "";
  result = s21_to_lower(input);
  ck_assert_str_eq(result, "");
  free(result);

  input = NULL;
  result = s21_to_lower(input);
  ck_assert_ptr_eq(result, NULL);

  input = "hello";
  result = s21_to_lower(input);
  ck_assert_str_eq(result, "hello");
  free(result);

  input = "HELLO, WORLD!";
  result = s21_to_lower(input);
  ck_assert_str_eq(result, "hello, world!");
  free(result);

  input = "H3LL0";
  result = s21_to_lower(input);
  ck_assert_str_eq(result, "h3ll0");
  free(result);

  input = "  HELLO  ";
  result = s21_to_lower(input);
  ck_assert_str_eq(result, "  hello  ");
  free(result);

  input = "HELLO\0WORLD";
  result = s21_to_lower(input);
  ck_assert_str_eq(result, "hello");
  free(result);

  input = "HELLO!@#$%^&*()_+";
  result = s21_to_lower(input);
  ck_assert_str_eq(result, "hello!@#$%^&*()_+");
  free(result);

  input = "HeLlO WoRlD";
  result = s21_to_lower(input);
  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_s21_insert) {
  const char *src = "Hello!";
  const char *str = " world";
  size_t start_index = 5;
  char *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "Hello world!");
  free(result);

  src = "world!";
  str = "Hello ";
  start_index = 0;
  result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "Hello world!");
  free(result);

  src = "Hello";
  str = " world!";
  start_index = 5;
  result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "Hello world!");
  free(result);

  src = "";
  str = "Hello";
  start_index = 0;
  result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "Hello");
  free(result);

  src = "Hello";
  str = "";
  start_index = 3;
  result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "Hello");
  free(result);

  src = "Hello";
  str = " world";
  start_index = 10;
  result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(result, NULL);

  src = NULL;
  str = "Hello";
  start_index = 0;
  result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(result, NULL);

  src = "Hello";
  str = NULL;
  start_index = 0;
  result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_s21_trim) {
  const char *src = "  Hello World  ";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello World");
  free(result);

  src = "###Hello World###";
  trim_chars = "#";
  result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello World");
  free(result);

  src = "Hello World###";
  trim_chars = "#";
  result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello World");
  free(result);

  src = "Hello World";
  trim_chars = "#";
  result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello World");
  free(result);

  src = "";
  trim_chars = " ";
  result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);

  src = "###";
  trim_chars = "#";
  result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);

  src = "Hello World";
  trim_chars = NULL;
  result = s21_trim(src, trim_chars);
  ck_assert_ptr_eq(result, NULL);

  src = NULL;
  trim_chars = " ";
  result = s21_trim(src, trim_chars);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

#endif
