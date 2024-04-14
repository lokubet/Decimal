#include <math.h>
#include <stdio.h>

#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int ret = 0;
  if (dst == NULL) {
    ret = 1;
  } else {
    *dst = 0;
    for (int i = 0; i < BITS_IN_INT * 3; ++i) {
      *dst += s21_get_nth_bit_of_decimal(&src, i) * pow(2, i);
    }
    int ten_deg = s21_get_10_deg(&src);
    *dst *= pow(10, -ten_deg);
    if (s21_get_nth_bit(src.bits[3], 31)) {
      *dst = -(*dst);
    }
  }
  return ret;
}