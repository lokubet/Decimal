#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

#define MIN_DECIMAL 1e-28f
#define MAX_DECIMAL 79228162514264337593543950335.00f
#define MAX_DIGITS 7

void s21_num_to_7_digits_form(float *src_abs, int *scale, int *digits) {
  long double q = *src_abs;
  while ((int)q == 0) {
    q *= 10;
    ++(*(scale));
  }
  *digits = log10(q) + 1;
  if (*digits < MAX_DIGITS && *scale <= 28) {
    q *= pow(10, MAX_DIGITS - *digits);
    *scale += MAX_DIGITS - *digits;
  }
  if (*digits > MAX_DIGITS) {
    q *= pow(10, MAX_DIGITS - *digits);
  }
  while ((*scale > 0 && (int)q % 10 == 0) || *scale > 28) {
    q /= 10;
    --(*(scale));
  }
  q = roundl(q);
  *src_abs = q;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 0;
  float src_abs = fabsf(src);
  if (dst == NULL) {
    ret = 1;
  } else if (isnan(src) || isinf(src) ||
             (src_abs < MIN_DECIMAL && src_abs > 0.0) ||
             src_abs > MAX_DECIMAL) {
    s21_make_zero_decimal(dst);
    ret = 1;
  } else if (src == 0) {
    s21_make_zero_decimal(dst);
  } else {
    s21_make_zero_decimal(dst);
    int binary = *((int *)&src);
    dst->bits[3] |= (s21_get_nth_bit(binary, 31) << 31);
    int scale = 0, digits = 0;
    s21_num_to_7_digits_form(&src_abs, &scale, &digits);
    dst->bits[0] = (int)src_abs;
    dst->bits[3] |= (scale << 16);

    if (digits > MAX_DIGITS) {
      s21_mul_by_10(dst, digits - MAX_DIGITS);
    }
  }
  return ret;
}
