#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL || (value.bits[3] << 1 >> 17) > 28) {
    error = 1;
  } else {
    s21_copy(value, result);
    result->bits[3] ^= 0x80000000;
  }
  return error;
}