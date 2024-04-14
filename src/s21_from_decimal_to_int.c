#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int ret = 0;
  int exp = s21_get_10_deg(&src);
  if (dst == NULL || exp > 28) {
    ret = 1;
  } else {
    s21_truncate(src, &src);
    if (src.bits[1] != 0 || src.bits[2] != 0 ||
        s21_get_nth_bit(src.bits[0], 31)) {
      ret = 1;
    } else {
      *dst = src.bits[0];
      if (s21_get_nth_bit(src.bits[3], 31)) *dst *= -1;
    }
  }
  return ret;
}
