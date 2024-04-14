#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dest) {
  int ret = 0;
  if (dest == NULL) {
    ret = 1;
  } else {
    s21_make_zero_decimal(dest);
    dest->bits[0] = abs(src);
    dest->bits[3] |= (s21_get_nth_bit(src, 31) << 31);
  }
  return ret;
}
