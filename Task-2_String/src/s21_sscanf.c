#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "s21_string.h"

static const char *skip_whitespace(const char *str) {
  while (*str && isspace(*str)) {
    str++;
  }
  return str;
}

static const char *read_int(const char *str, int base, void *out, char length,
                            int suppress, int width) {
  long long value = 0;
  int sign = 1;

  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }

  while (*str && isdigit(*str) && width > 0) {
    value = value * base + (*str - '0');
    str++;
    width--;
  }

  if (!suppress && out) {
    if (length == 'h') {
      *(short *)out = (short)(value * sign);
    } else if (length == 'l') {
      *(long *)out = (long)(value * sign);
    } else {
      *(int *)out = (int)(value * sign);
    }
  }

  return str;
}

static const char *string_to_float(const char *str, void *result, char length) {
  long double value = 0.0;
  long double fraction = 0.0;
  long double divisor = 1.0;
  int sign = 1;
  int exponent = 0;
  int decimal_point = 0;

  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }

  // reading of integer part
  while (*str >= '0' && *str <= '9') {
    value = value * 10.0 + (*str - '0');
    str++;
  }

  // reading of fractional part
  if (*str == '.') {
    decimal_point = 1;
    str++;
    while (*str >= '0' && *str <= '9') {
      fraction = fraction * 10.0 + (*str - '0');
      divisor *= 10.0;
      str++;
    }
  }

  if (*str == 'e' || *str == 'E') {
    str++;
    int exp_sign = 1;
    if (*str == '-') {
      exp_sign = -1;
      str++;
    } else if (*str == '+') {
      str++;
    }
    while (*str >= '0' && *str <= '9') {
      exponent = exponent * 10 + (*str - '0');
      str++;
    }
    exponent *= exp_sign;
  }

  if (value == 0 && fraction == 0 && !decimal_point) return s21_NULL;

  long double result_value = sign * (value + fraction / divisor);

  // exponent implementation
  if (exponent != 0) {
    if (exponent > 0) {
      for (int i = 0; i < exponent; i++) {
        result_value *= 10.0;
      }
    } else {
      for (int i = 0; i > exponent; i--) {
        result_value /= 10.0;
      }
    }
  }

  // save result according to length
  if (length == 'l') {
    *(double *)result = (double)result_value;
  } else if (length == 'L') {
    *(long double *)result = result_value;
  } else {
    *(float *)result = (float)result_value;
  }

  return str;
}

static const char *hex_string_to_int(const char *str, unsigned long *result,
                                     int width) {
  *result = 0;
  int parsed = 0;

  // skip "0x" or "0X" if have
  if (width > 2 && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
    width -= 2;
  }

  // processing digits and symbols a-f / A-F according to width
  while (*str && width > 0) {
    if (*str >= '0' && *str <= '9') {
      *result = *result * 16 + (*str - '0');
      parsed = 1;
    } else if (*str >= 'A' && *str <= 'F') {
      *result = *result * 16 + (*str - 'A' + 10);
      parsed = 1;
    } else if (*str >= 'a' && *str <= 'f') {
      *result = *result * 16 + (*str - 'a' + 10);
      parsed = 1;
    } else {
      break;
    }
    str++;
    width--;
  }

  return parsed ? str : s21_NULL;
}

static const char *read_char(const char *str, char *out, int suppress) {
  if (!suppress && out != s21_NULL) {
    *out = *str;
  }
  return str + 1;
}

static const char *string_to_pointer(const char *str, void **result) {
  unsigned long value = 0;
  int res = 0;
  const char *new_str = hex_string_to_int(str, &value, INT_MAX);
  if (new_str != s21_NULL) {
    *result = (void *)(uintptr_t)value;
    res = 1;
  }
  return res ? new_str : s21_NULL;
}

static const char *read_string(const char *str, char *out, int width,
                               int suppress) {
  int count = 0;
  while (*str && !isspace(*str) && (width == 0 || count < width)) {
    if (!suppress) {
      *out++ = *str;
    }
    str++;
    count++;
  }
  if (!suppress) {
    *out = '\0';
  }
  return str;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int matched = 0;
  str = skip_whitespace(str);
  const char *input_start = str;

  while (*format) {
    if (isspace(*format)) {
      format++;
      str = skip_whitespace(str);
    } else if (*format == '%') {
      format++;
      int suppress = 0, width = 0;
      char length = 0;

      if (*format == '*') {
        suppress = 1;
        format++;
      }

      if (*format >= '0' && *format <= '9') {
        width = 0;
        while (*format >= '0' && *format <= '9') {
          width = width * 10 + (*format - '0');
          format++;
        }
      }

      if (*format == 'h' || *format == 'l' || *format == 'L') {
        length = *format;
        format++;
      }

      if (*format == 'f' || *format == 'e' || *format == 'E' ||
          *format == 'g' || *format == 'G') {
        void *f_arg = suppress ? s21_NULL : va_arg(args, void *);

        const char *new_str = string_to_float(str, f_arg, length);
        if (new_str != s21_NULL) {
          str = new_str;
          if (!suppress) matched++;
        } else {
          break;  // parsing error
        }

      } else if (*format == 'd' || *format == 'i') {
        void *out = suppress ? s21_NULL : va_arg(args, void *);
        str = read_int(str, 10, out, length, suppress, width ? width : INT_MAX);
        if (!suppress) matched++;
      } else if (*format == 'u') {
        void *out = suppress ? s21_NULL : va_arg(args, void *);
        str = read_int(str, 10, out, length, suppress, width ? width : INT_MAX);
        if (!suppress) matched++;
      } else if (*format == 'x' || *format == 'X') {
        unsigned long temp_value = 0;
        unsigned int *x_arg =
            suppress ? s21_NULL : va_arg(args, unsigned int *);
        const char *new_str = hex_string_to_int(
            str, suppress ? &temp_value : (unsigned long *)x_arg,
            width ? width : INT_MAX);
        if (new_str != s21_NULL) {
          str = new_str;
          if (!suppress) matched++;
        } else {
          break;  // parsing error
        }

      } else if (*format == 'o') {
        void *out = suppress ? s21_NULL : va_arg(args, void *);
        str = read_int(str, 8, out, length, suppress, width ? width : INT_MAX);
        if (!suppress) matched++;
      } else if (*format == 's') {
        char *out = suppress ? s21_NULL : va_arg(args, char *);
        str = read_string(str, out, width ? width : INT_MAX, suppress);
        if (!suppress) matched++;
      } else if (*format == 'n') {
        int *out = va_arg(args, int *);
        if (!suppress) {
          *out = (int)(str - input_start);
        }
      } else if (*format == 'c') {
        char *out = suppress ? s21_NULL : va_arg(args, char *);
        str = read_char(str, out, suppress);
        if (!suppress) matched++;
      } else if (*format == 'p') {
        void **p_arg = suppress ? s21_NULL : va_arg(args, void **);
        const char *new_str = string_to_pointer(str, p_arg);
        if (new_str != s21_NULL) {
          str = new_str;
          if (!suppress) matched++;
        } else {
          break;  // pointer transformation error
        }
      } else if (*format == '%') {
        if (*str == '%') {
          str++;
        } else {
          matched -= 1;
          break;
        }
      }

      format++;
    }
  }

  va_end(args);
  return matched;
}
