#include "s21_string.h"

s21_size_t my_strlen(const char *str) {
  s21_size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t lengthS1 = my_strlen(str1);
  s21_size_t lengthS2 = my_strlen(str2);
  char *result = s21_NULL;

  for (s21_size_t i = 0; i < lengthS1 && result == s21_NULL; i++) {
    for (s21_size_t j = 0; j < lengthS2; j++) {
      if (str1[i] == str2[j]) {
        result = (char *)&str1[i];
        break;
      }
    }
  }

  return result;
}
