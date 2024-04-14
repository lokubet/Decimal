#include <stdio.h>

#include "s21_decimal.h"

void s21_div_main(s21_extended_decimal *v1, s21_extended_decimal *v2,
                  s21_extended_decimal *quotient) {
  int counter = 1;
  while (!getBit_l(*v2, 191)) {
    leftShift_l(v2, 1);
    ++counter;
  }
  while (counter > 0) {
    leftShift_l(quotient, 1);
    if (s21_is_greater_or_equal_l(*v1, *v2)) {
      s21_sub_l(*v1, *v2, v1);
      setBit_l(quotient, 0, 1);
    } else {
      setBit_l(quotient, 0, 0);
    }
    rightShift_l(v2, 1);
    --counter;
  }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0, sign1 = 0, sign2 = 0, scale = 0;
  int exp1 = s21_get_10_deg(&value_1), exp2 = s21_get_10_deg(&value_2);
  s21_extended_decimal v1, v2, result_l, quotient;
  if (s21_is_zero(value_2)) {
    ret = 3;
  } else if (result != NULL && s21_is_zero(value_1)) {
    s21_make_zero_decimal(result);
  } else if (result != NULL && exp1 <= 28 && exp2 < 28) {
    sign1 = s21_get_nth_bit(value_1.bits[3], 31);
    sign2 = s21_get_nth_bit(value_2.bits[3], 31);
    setSign(&value_1, 0);
    setSign(&value_2, 0);
    v1 = s21_from_d_to_big(value_1);
    v2 = s21_from_d_to_big(value_2);
    int diff = exp1 - exp2;
    while (diff < 0) {
      increaseScale_l(&v1, abs(diff));
      ++diff;
    }
    if (diff > 0) {
      v1.bits[6] = 0;
      v2.bits[6] = 0;
      scale += diff;
    }
    while (s21_is_less_l(v1, v2)) {
      s21_mul_by_10_l(&v1, 1);
      ++scale;
    }
    s21_make_zero_extended_decimal(&quotient);
    s21_make_zero_extended_decimal(&result_l);
    s21_div_main(&v1, &v2, &quotient);
    v2 = s21_from_d_to_big(value_2);
    s21_copy_l(quotient, &result_l);
    while (!s21_is_zero_l(v1) && scale < 28) {
      s21_mul_by_10_l(&v1, 1);
      s21_make_zero_extended_decimal(&quotient);
      s21_div_main(&v1, &v2, &quotient);
      s21_mul_by_10_l(&result_l, 1);
      s21_add_l(result_l, quotient, &result_l);
      ++scale;
    }
    ret = s21_from_big_to_small(result_l, result, scale);
    if (sign1 != sign2) {
      s21_negate(*result, result);
    }
    if (ret == 1 && sign1 != sign2) {
      ret = 2;
    }
  }
  return ret;
}
