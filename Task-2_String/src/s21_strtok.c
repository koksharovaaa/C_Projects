#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  char *start = s21_NULL;
  static char *nextToken = s21_NULL;
  if (str) {
    nextToken = str;
  }

  if (nextToken) {
    while (*nextToken != '\0' && s21_strchr(delim, *nextToken) != s21_NULL) {
      nextToken++;
    }
  }

  if (nextToken && *nextToken != '\0') {
    start = nextToken;

    while (*nextToken != '\0' && s21_strchr(delim, *nextToken) == s21_NULL) {
      nextToken++;
    }

    if (*nextToken == '\0') {
      nextToken = s21_NULL;
    } else {
      *nextToken = '\0';
      nextToken++;
    }
  }

  return start;
}
