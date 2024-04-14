#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0, exp = (value.bits[3] << 1 >> 17);
  if (result == NULL || exp > 28) {
    error = 1;
  } else if (s21_is_zero(value)) {
    s21_copy(value, result);
    result->bits[3] &= 0x80000000;
  } else {
    int last_num = 0, flag = 0;
    if (s21_get_nth_bit_of_decimal(&value, 127)) {
      while (exp) {
        last_num = s21_div10(&value, 1);
        value.bits[3] -= 0x00010000;
        if (last_num) {
          flag = 1;
        }
        exp--;
      }
      if (flag) {
        s21_decimal minus_one = {{1, 0, 0, 0x80000000}};
        s21_add(value, minus_one, &value);
      }
      s21_copy(value, result);
    } else {
      s21_truncate(value, result);
    }
  }
  return error;
}