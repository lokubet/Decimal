#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int flag = 1;
  if (s21_is_zero(a) && s21_is_zero(b)) {
    flag = 1;
  } else if (s21_get_nth_bit_of_decimal(&a, 127) !=
             s21_get_nth_bit_of_decimal(&b, 127)) {
    flag = 0;
  } else {
    s21_remove_zeros(&a);
    s21_remove_zeros(&b);
    a.bits[3] &= 0x01111111;
    b.bits[3] &= 0x01111111;
    s21_normalization(&a, &b);
    for (int i = 0; i < 4; i++) {
      if (a.bits[i] != b.bits[i]) {
        flag = 0;
      }
    }
  }
  return flag;
}