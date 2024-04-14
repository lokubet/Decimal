#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  int flag = 0, sign_bit_a = s21_get_nth_bit_of_decimal(&a, 127),
      sign_bit_b = s21_get_nth_bit_of_decimal(&b, 127);
  if (s21_is_equal(a, b)) {
    flag = 0;
  } else if ((sign_bit_a) && (sign_bit_b == 0)) {
    flag = 1;
  } else if ((sign_bit_a == 0) && (sign_bit_b)) {
    flag = 0;
  } else {
    a.bits[3] &= 0b01111111111111111111111111111111;
    b.bits[3] &= 0b01111111111111111111111111111111;
    s21_normalization(&a, &b);
    for (int i = 2; i >= 0; i--) {
      unsigned int left = a.bits[i], right = b.bits[i];
      if (left < right) {
        flag = 1;
        i = -2;
      } else if (left > right) {
        flag = 0;
        break;
      }
    }
    if (sign_bit_a) flag = flag ? 0 : 1;
  }
  return flag;
}