#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_string.h"

typedef struct {
  char sign;  //_+
  int minus;
  int sharp;
  int zero;
} Flags;

typedef struct {
  Flags flags;
  int width;
  int precision;
  char length;
  char specifier;
} Format;

int parse_format(const char *ptr, Format *f);
void write_argument_to_string(char *str, int *count, va_list *args, Format *f);
void write_char_arg_to_string(char *str, int *count, va_list *args,
                              const Format *f);
void write_int_arg_to_string(char *str, int *count, va_list *args, Format *f);
void write_float_arg_to_string(char *str, int *count, va_list *args, Format *f);
void write_str_arg_to_string(char *str, int *count, va_list *args, Format *f);
void write_uint_arg_to_string(char *str, int *count, va_list *args, Format *f);

void write_chars_to_string(char *str, int *count, char c, int number_of_c);
char *uint_to_string(unsigned long long int number, int base, int small_letter);
char *ldouble_to_string(long double number);
void get_integer_frac_parts(long double *arg_f, char **str_int, char **str_frac,
                            int *len_of_spaces, Format *f);
int remove_zeros(char *str);
int add_zeros_at_start(char **str, int count);

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  Format f;
  int parse_result;

  int count = 0;

  while (*format) {
    switch (*format) {
      case '%':
        parse_result = parse_format(format, &f);
        if (parse_result == 1)
          str[count++] = *format;  //%
        else if (parse_result > 1) {
          write_argument_to_string(str, &count, &args, &f);
        }
        format += parse_result;
        break;
      default:
        str[count++] = *format++;
    }
  }

  str[count] = '\0';
  va_end(args);
  if (!count) count = -1;
  return count;
}

int parse_format(const char *ptr, Format *f) {
  // Проверка на наличие символа '%', ПРЕДВАРИТЕЛЬНАЯ ПРОВЕРКА АРГУМЕНТА
  if (*ptr != '%') return 0;

  int format_string_length = 0;
  int set_default_precision = 1;
  ptr++;  // Пропускаем символ '%'
  format_string_length++;

  Flags flags = {0};
  f->flags = flags;
  while (s21_strchr("-+ 0#", *ptr)) {
    switch (*ptr) {
      case ' ':
        if (f->flags.sign != '+') f->flags.sign = ' ';
        break;
      case '-':
        f->flags.minus = 1;
        break;
      case '+':
        f->flags.sign = '+';
        break;
      case '#':
        f->flags.sharp = 1;
        break;
      case '0':
        f->flags.zero = 1;
        break;
      default:;
    }
    ptr++;
    format_string_length++;
  }

  f->width = 0;
  if (*ptr >= '0' && *ptr <= '9')
    f->width = atoi(ptr);
  else if (*ptr == '*') {
    f->width = -1;
    ptr++;
    format_string_length++;
  }
  while (*ptr >= '0' && *ptr <= '9') {
    ptr++;
    format_string_length++;
  }

  if (*ptr == '.') {
    f->precision = 0;
    set_default_precision = 0;
    ptr++;
    format_string_length++;
    if (*ptr >= '0' && *ptr <= '9')
      f->precision = atoi(ptr);
    else if (*ptr == '*') {
      f->precision = -1;
      ptr++;
      format_string_length++;
    }
    while (*ptr >= '0' && *ptr <= '9') {
      ptr++;
      format_string_length++;
    }
  }

  f->length = 0;
  if (s21_strchr("hlL", *ptr)) {
    f->length = *ptr++;
    format_string_length++;
  }

  f->specifier = 0;
  if (s21_strchr("cdfsugGeExXop%", *ptr)) {
    f->specifier = *ptr;
    format_string_length++;
  } else
    format_string_length = 1;

  if (set_default_precision)
    if (f->specifier == 's')
      f->precision = -2;
    else if (f->specifier == 'e' || f->specifier == 'E' ||
             f->specifier == 'f' || f->specifier == 'g' || f->specifier == 'G')
      f->precision = 6;
    else
      f->precision = 1;
  else if (f->specifier != 'f' && f->specifier != 'e' && f->specifier != 'E' &&
           f->specifier != 'g' && f->specifier != 'G')
    f->flags.zero = 0;

  return format_string_length;
}

void write_argument_to_string(char *str, int *count, va_list *args, Format *f) {
  if (f->width == -1) f->width = va_arg(*args, int);
  if (f->precision == -1) f->precision = va_arg(*args, int);

  switch (f->specifier) {
    case 'c':
      write_char_arg_to_string(str, count, args, f);
      break;
    case 'd':
      write_int_arg_to_string(str, count, args, f);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      write_float_arg_to_string(str, count, args, f);
      break;
    case 's':
      write_str_arg_to_string(str, count, args, f);
      break;
    case 'u':
    case 'o':
    case 'x':
    case 'X':
    case 'p':
      write_uint_arg_to_string(str, count, args, f);
      break;
    case '%':
      str[(*count)++] = '%';
      break;
  }
}

void write_char_arg_to_string(char *str, int *count, va_list *args,
                              const Format *f) {
  int len_of_spaces = f->width - 1;
  if (!f->flags.minus) write_chars_to_string(str, count, ' ', len_of_spaces);

  if (f->length == 'l' || f->length == 'L')
    *(str + (*count)++) = (char)va_arg(*args, wchar_t);
  else
    *(str + (*count)++) = (char)va_arg(*args, int);
  // str[(*count)++] = (char) va_arg(*args, int);

  if (f->flags.minus) write_chars_to_string(str, count, ' ', len_of_spaces);
}

void write_int_arg_to_string(char *str, int *count, va_list *args, Format *f) {
  int len_of_spaces = 0;
  long int arg_d;

  if (f->length == 'h')
    arg_d = (long int)(short int)va_arg(*args, int);  // int
  else if (f->length == 'l' || f->length == 'L')
    arg_d = va_arg(*args, long int);
  else
    arg_d = (long int)va_arg(*args, int);  // int

  if (arg_d < 0) {
    arg_d = -arg_d;
    f->flags.sign = '-';
  }

  char *str_d = uint_to_string((unsigned long long int)arg_d, 10, 0);

  if (s21_strlen(str_d) < (s21_size_t)f->precision)
    add_zeros_at_start(&str_d, f->precision - s21_strlen(str_d));

  len_of_spaces += f->width - s21_strlen(str_d) - (f->flags.sign > 0);
  len_of_spaces += (f->precision == 0 && arg_d == 0);  // print nothing

  if (!f->flags.minus && !f->flags.zero)
    write_chars_to_string(str, count, ' ', len_of_spaces);

  if (f->flags.sign) str[(*count)++] = f->flags.sign;

  if (!f->flags.minus && f->flags.zero)
    write_chars_to_string(str, count, '0', len_of_spaces);

  if (!(f->precision == 0 && arg_d == 0)) {
    s21_strncpy(str + (*count), str_d, s21_strlen(str_d) + 1);
    *count += s21_strlen(str_d);
  }

  if (f->flags.minus) write_chars_to_string(str, count, ' ', len_of_spaces);

  free(str_d);
}

void write_float_arg_to_string(char *str, int *count, va_list *args,
                               Format *f) {
  int len_of_spaces = 0;
  long double arg_f;
  int number_for_exp = 0;
  char sign_for_exp = '+';
  double epsilon = 1e-13;
  char *str_f_int = s21_NULL;
  char *str_f_frac = s21_NULL;
  char *number_for_exp_s = s21_NULL;

  if (f->length == 'L')
    arg_f = va_arg(*args, long double);
  else
    arg_f = (long double)va_arg(*args, double);

  if (arg_f < 0) {
    arg_f = -arg_f;
    f->flags.sign = '-';
  }

  if (f->specifier == 'e' || f->specifier == 'E' ||
      ((f->specifier == 'g' || f->specifier == 'G') &&
       ((roundl(arg_f) >= pow(10, f->precision) && roundl(arg_f) >= 10) ||
        epsilon < 1e-4 - arg_f))) {
    while (arg_f >= 10) {
      arg_f /= 10;
      number_for_exp++;
    }

    while ((unsigned long long int)arg_f == 0 && arg_f != 0.0) {
      arg_f *= 10;
      number_for_exp++;
      sign_for_exp = '-';
    }

    if ((f->specifier == 'g' || f->specifier == 'G')) {
      f->precision--;
    }

    if (/*f->precision <= 0 &&*/ roundl(arg_f) >= 10) {
      arg_f = roundl(arg_f);
      arg_f /= 10;
      if (sign_for_exp == '+')
        number_for_exp++;
      else
        number_for_exp--;
    }

    number_for_exp_s =
        uint_to_string((unsigned long long int)number_for_exp, 10, 0);
    len_of_spaces -=
        (2 + (number_for_exp < 10) + s21_strlen(number_for_exp_s));  // e+02
    len_of_spaces -=
        2 * ((f->precision <= 0) && !(f->flags.sharp) &&
             ((f->specifier == 'g' || f->specifier == 'G')));  // not print .0

  } else if (f->specifier == 'g' || f->specifier == 'G') {
    int reduce_precision_count = 0;

    do {
      arg_f *= 10;
      reduce_precision_count++;
    } while (arg_f < pow(10, f->precision));

    arg_f /= 10;

    if (roundl(arg_f) >= 1 && (unsigned long long int)arg_f != 0) {
      arg_f = roundl(arg_f);
      f->precision = reduce_precision_count - 1;

    } else
      f->precision = reduce_precision_count;

    arg_f /= pow(10, reduce_precision_count - 1);

    if (!f->precision) len_of_spaces -= 2 * (!f->flags.sharp);  // .0
  }

  get_integer_frac_parts(&arg_f, &str_f_int, &str_f_frac, &len_of_spaces, f);

  if (number_for_exp_s != s21_NULL)
    if ((f->specifier == 'g' || f->specifier == 'G') &&
        (!s21_strncmp(str_f_int, "1", 2) /*&& number_for_exp == 0*/)) {
      len_of_spaces += (2 + /*(number_for_exp < 10)*/ 1 +
                        s21_strlen(number_for_exp_s));  // not print e+02
      len_of_spaces += 2 * f->flags.sharp;              // .0
    }

  if (s21_strlen(str_f_frac) < (s21_size_t)f->precision)
    len_of_spaces -=
        add_zeros_at_start(&str_f_frac, f->precision - s21_strlen(str_f_frac));

  if ((f->specifier == 'g' || f->specifier == 'G') && !f->flags.sharp)
    len_of_spaces += remove_zeros(str_f_frac);

  len_of_spaces += !(str_f_frac[0]);  // if have frac_part

  if (!f->flags.minus && !f->flags.zero)
    write_chars_to_string(str, count, ' ', len_of_spaces);

  if (f->flags.sign) str[(*count)++] = f->flags.sign;

  if (!f->flags.minus && f->flags.zero)
    write_chars_to_string(str, count, '0', len_of_spaces);

  s21_strncpy(str + (*count), str_f_int, s21_strlen(str_f_int) + 1);

  *count += s21_strlen(str_f_int);

  if ((f->precision > 0 || f->flags.sharp) && str_f_frac[0]) {
    str[(*count)++] = '.';
  }

  if (f->precision > 0) {
    s21_strncpy(str + (*count), str_f_frac, s21_strlen(str_f_frac));
    *count += s21_strlen(str_f_frac);
  }

  if (number_for_exp_s != s21_NULL) {
    if (f->specifier == 'e' || f->specifier == 'E' ||
        ((f->specifier == 'g' || f->specifier == 'G') &&
         !(!s21_strncmp(str_f_int, "1", 2) && number_for_exp == 0))) {
      if (f->specifier == 'g')
        f->specifier = 'e';
      else if (f->specifier == 'G')
        f->specifier = 'E';

      str[(*count)++] = f->specifier;

      str[(*count)++] = sign_for_exp;

      if (number_for_exp < 10) str[(*count)++] = '0';

      s21_strncpy(str + (*count), number_for_exp_s,
                  s21_strlen(number_for_exp_s) + 1);
      *count += s21_strlen(number_for_exp_s);
    }
  }

  if (f->flags.minus) write_chars_to_string(str, count, ' ', len_of_spaces);

  if (str_f_int != s21_NULL) free(str_f_int);

  if (str_f_frac != s21_NULL) free(str_f_frac);

  if (number_for_exp_s != s21_NULL) free(number_for_exp_s);
}

void write_str_arg_to_string(char *str, int *count, va_list *args, Format *f) {
  int len_of_spaces = 0;

  char *arg_s = s21_NULL;
  const wchar_t *wide_str = s21_NULL;

  if (f->length == 'l' || f->length == 'L') {
    wide_str = va_arg(*args, wchar_t *);
  } else
    arg_s = va_arg(*args, char *);

  if (f->length == 'l' || f->length == 'L') {
    s21_size_t len = wcslen(wide_str) + 1;

    arg_s = malloc(len * sizeof(char));

    s21_size_t convertedChars = wcstombs(arg_s, wide_str, len);

    if (convertedChars == (s21_size_t)-1) free(arg_s);
  }

  if (f->precision > (int)s21_strlen(arg_s) || f->precision == -2)
    f->precision = s21_strlen(arg_s);

  len_of_spaces += f->width - f->precision;

  if (!f->flags.minus) write_chars_to_string(str, count, ' ', len_of_spaces);

  for (int i = 0; i < f->precision; i++) str[(*count)++] = arg_s[i];

  if (f->flags.minus) write_chars_to_string(str, count, ' ', len_of_spaces);

  if (f->length == 'l' || f->length == 'L') free(arg_s);
}

void write_uint_arg_to_string(char *str, int *count, va_list *args, Format *f) {
  int len_of_spaces = 0;

  unsigned long long int arg_u;
  if (f->specifier == 'p')
    arg_u = va_arg(*args, unsigned long long int);
  else if (f->length == 'h')
    arg_u =
        (unsigned long long int)(unsigned short int)va_arg(*args, unsigned int);
  else if (f->length == 'l' || f->length == 'L')
    arg_u = (unsigned long long int)va_arg(*args, unsigned long int);
  else
    arg_u = (unsigned long long int)va_arg(*args, unsigned int);

  char *str_u = s21_NULL;
  if (f->specifier == 'u')
    str_u = uint_to_string(arg_u, 10, 0);
  else if (f->specifier == 'o')
    str_u = uint_to_string(arg_u, 8, 0);
  else if (f->specifier == 'X')
    str_u = uint_to_string(arg_u, 16, 0);
  else if (f->specifier == 'x' || f->specifier == 'p')
    str_u = uint_to_string(arg_u, 16, 1);

  len_of_spaces +=
      f->width - s21_strlen(str_u) *
                     (!(f->specifier == 'p' && arg_u == 0));  // if not (nil)
  len_of_spaces -=
      (f->specifier == 'o' && f->flags.sharp && arg_u > 0);  // 0 prefix
  len_of_spaces -= 2 * ((f->specifier == 'x' || f->specifier == 'X') &&
                        f->flags.sharp && arg_u >= 1);       // 0x
  len_of_spaces -= 2 * (f->specifier == 'p' && arg_u >= 1);  // 0x
  len_of_spaces -= 5 * (f->specifier == 'p' && arg_u == 0);  // (nil)
  len_of_spaces -=
      (f->specifier == 'p' && f->flags.sign > 0 && arg_u >= 1);  // +_
  len_of_spaces += (f->precision == 0 && arg_u == 0) &&
                   f->specifier != 'p';  // print nothing
  len_of_spaces -= (f->specifier == 'o' && f->flags.sharp && arg_u == 0 &&
                    f->precision == 0);  // 0 exception

  if ((s21_strlen(str_u) < (s21_size_t)f->precision) &&
      !(f->specifier == 'p' && arg_u == 0))
    len_of_spaces -= add_zeros_at_start(
        &str_u, f->precision - s21_strlen(str_u) -
                    (f->specifier == 'o' && f->flags.sharp && arg_u > 0));

  if (!f->flags.minus &&
      (!f->flags.zero || (f->specifier == 'p' && arg_u == 0)))
    write_chars_to_string(str, count, ' ', len_of_spaces);

  if (f->specifier == 'p' && f->flags.sign > 0 && arg_u > 0)
    str[(*count)++] = f->flags.sign;

  if ((f->specifier == 'o' || f->specifier == 'x' || f->specifier == 'X') &&
      f->flags.sharp && arg_u > 0)
    str[(*count)++] = '0';

  if (f->specifier == 'p' && arg_u > 0) str[(*count)++] = '0';

  if ((f->specifier == 'x' || f->specifier == 'X') && f->flags.sharp &&
      arg_u > 0)
    str[(*count)++] = f->specifier;

  if (f->specifier == 'p' && arg_u > 0) str[(*count)++] = 'x';

  if ((!f->flags.minus && f->flags.zero) &&
      !(f->specifier == 'p' && arg_u == 0))
    write_chars_to_string(str, count, '0', len_of_spaces);

  if ((f->specifier != 'p' && !(f->precision == 0 && arg_u == 0)) ||
      (f->specifier == 'p' && arg_u > 0) ||
      (f->specifier == 'o' && f->flags.sharp && arg_u == 0 &&
       f->precision == 0)) {
    s21_strncpy(str + (*count), str_u, s21_strlen(str_u) + 1);
    *count += s21_strlen(str_u);
  } else if (f->specifier == 'p' && arg_u == 0) {
    s21_strncpy(str + (*count), "(nil)", 6);
    *count += 5;
  }

  if (f->flags.minus) write_chars_to_string(str, count, ' ', len_of_spaces);

  if (str_u != s21_NULL) free(str_u);
}

void get_integer_frac_parts(long double *arg_f, char **str_int, char **str_frac,
                            int *len_of_spaces, Format *f) {
  long double integer_part_arg;
  long double fractional_part_arg;

  fractional_part_arg = modfl(*arg_f, &integer_part_arg);

  for (int i = 0; i < f->precision; i++) fractional_part_arg *= 10;

  fractional_part_arg = roundl(fractional_part_arg);

  for (int i = 0; i < f->precision; i++) fractional_part_arg /= 10;

  *arg_f = integer_part_arg + fractional_part_arg;

  fractional_part_arg = modfl(*arg_f, &integer_part_arg);

  for (int i = 0; i < f->precision; i++) fractional_part_arg *= 10;

  fractional_part_arg = roundl(fractional_part_arg);

  *str_int = ldouble_to_string(integer_part_arg);
  *str_frac = ldouble_to_string(fractional_part_arg);

  *len_of_spaces += f->width - s21_strlen(*str_int);
  *len_of_spaces -= (f->precision > 0) * s21_strlen(*str_frac);
  *len_of_spaces -= (f->precision > 0 || f->flags.sharp);
  *len_of_spaces -= (f->flags.sign > 0);
}

void write_chars_to_string(char *str, int *count, char c, int number_of_c) {
  for (int i = 0; i < number_of_c; i++) str[(*count)++] = c;
}

char *uint_to_string(unsigned long long int number, int base,
                     int small_letter) {
  int count = 1;
  char *temp;
  char *result = (char *)calloc(2, sizeof(char));
  if (number == 0) result[0] = '0';
  while (number != 0) {
    temp = realloc(result, ++count * sizeof(char));
    if (temp != s21_NULL) result = temp;

    for (int i = count - 1; i > 0; i--) result[i] = result[i - 1];
    if (number % base <= 9)
      result[0] = number % base + '0';
    else
      result[0] = number % base - 10 + (small_letter ? 'a' : 'A');
    number /= base;
  }
  return result;
}

char *ldouble_to_string(long double number) {
  int count = 1;
  char *temp;
  char *result = (char *)calloc(2, sizeof(char));
  if (number == 0) result[0] = '0';
  while (number >= 1) {
    temp = realloc(result, ++count * sizeof(char));
    if (temp != s21_NULL) result = temp;

    for (int i = count - 1; i > 0; i--) result[i] = result[i - 1];

    result[0] = fmodl(number, 10) + '0';
    number /= 10;
    // modfl(number, &number);
  }
  return result;
}

int remove_zeros(char *str) {
  int count = s21_strlen(str) - 1;
  int result = 0;

  while (count >= 0 && str[count] == '0') {
    str[count] = 0;
    count--;
    result++;
  }
  return result;
}

int add_zeros_at_start(char **str, int count) {
  if (count <= 0) return 0;

  int len_of_str = s21_strlen(*str);
  *str = realloc(*str, len_of_str + 1 + count);

  if (*str != s21_NULL) {
    (*str)[len_of_str] = 0;
  }

  for (int i = len_of_str + count; i >= count; i--)
    (*str)[i] = (*str)[i - count];

  for (int i = 0; i < count; i++) (*str)[i] = '0';

  return count;
}
