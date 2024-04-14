#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0, exp = value.bits[3] << 1 >> 17;
  if (result == NULL || (exp > 28)) {
    error = 1;
  } else {
    if (exp > 0) {
      int last_num = s21_div10(&value, exp);
      value.bits[3] &= 0x80000000;
      s21_decimal one = {{1, 0, 0, 0}};
      if (s21_get_nth_bit_of_decimal(&value, 127)) {
        s21_negate(one, &one);
      }
      if ((value.bits[0] % 2 == 0 && last_num > 5) ||
          (value.bits[0] % 2 == 1 && last_num > 4)) {
        s21_add(value, one, &value);
      }
    }
    s21_copy(value, result);
  }
  return error;
}