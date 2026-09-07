#include "s21_string.h"

#ifdef __APPLE__
#define ERROR_COUNT 107
const char *macos_errors[ERROR_COUNT] = {
    "Success",                    // 0
    "Operation not permitted",    // 1
    "No such file or directory",  // 2
    "No such process",            // 3
    "Interrupted system call",    // 4
    "Input/output error",         // 5
    "Device not configured",      // 6
    "Argument list too long",     // 7
    "Exec format error",          // 8
    "Bad file descriptor",        // 9
    "No child processes",         // 10
    // ...
    "Too many levels of symbolic links",  // 63
    "Unknown error"                       // Запасное значение
};
#endif

// Для других платформ определяем дефолтные ошибки
#ifndef __APPLE__
const char *linux_errors[] = {
    "Success",                    // 0
    "Operation not permitted",    // 1
    "No such file or directory",  // 2
    "No such process",            // 3
    "Interrupted system call",    // 4
    "Input/output error",         // 5
    "Device not configured",      // 6
    "Argument list too long",     // 7
    "Exec format error",          // 8
    "Bad file descriptor",        // 9
    "No child processes",         // 10
    // ...
    "Unknown error"  // Запасное значение
};
#define ERROR_COUNT (sizeof(linux_errors) / sizeof(linux_errors[0]))
#endif

char *s21_strerror(int errnum) {
  static char unknown_error[64];
  unsigned int unsigned_errnum = (unsigned int)errnum;
  char *result = s21_NULL;

  if (unsigned_errnum < ERROR_COUNT) {
#ifdef __APPLE__
    result = (char *)macos_errors[unsigned_errnum];
#else
    result = (char *)linux_errors[unsigned_errnum];
#endif
  } else {
    s21_sprintf(unknown_error, "Unknown error %d", errnum);
    // snprintf(unknown_error, sizeof(unknown_error), "Unknown error %d",
    // errnum);
    result = unknown_error;
  }

  return result;
}
