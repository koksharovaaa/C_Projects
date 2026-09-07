#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;

  if (!*needle)
    result = (char *)haystack;
  else
    for (; *haystack; haystack++) {
      const char *h = haystack;
      const char *n = needle;

      while (*h && *n && (*h == *n)) {
        h++;
        n++;
      }

      if (!*n) {
        result = (char *)haystack;
        break;
      }
    }
  return result;
}
