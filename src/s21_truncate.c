#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0, exp = value.bits[3] << 1 >> 17;
  if (result == NULL || exp > 28) {
    error = 1;
  } else {
    s21_copy(value, result);
    s21_div10(result, exp);
    result->bits[3] &= 0x80000000;
  }
  return error;
}
