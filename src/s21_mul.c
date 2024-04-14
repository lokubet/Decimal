#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *res) {
  int result = 0;
  s21_extended_decimal long_res = {{0, 0, 0, 0, 0, 0}};
  s21_extended_decimal long_value1 = {{0, 0, 0, 0, 0, 0, 0}};
  s21_extended_decimal long_value2 = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_to_long_decimal(value_1, &long_value1);
  s21_decimal_to_long_decimal(value_2, &long_value2);
  s21_normalize_long(&long_value1, &long_value2);
  for (int i = 0; i < 96; i++) {
    if (getBit(value_2, i)) {
      s21_extended_decimal tmp = long_value1;
      s21_shift_left_long(&tmp, i);
      unsigned int temp = 0;
      s21_sum_full(long_res, tmp, &long_res, &temp);
    }
  }
  int res_power = s21_get_exponent(value_1) + s21_get_exponent(value_2);

  while (res_power > 28 || long_res.bits[5] || long_res.bits[4] ||
         long_res.bits[3]) {
    s21_divide_by_ten_long(&long_res);
    res_power--;
    if (res_power == 0) {
      result = 1;
      break;
    }
  }
  if (!result) {
    s21_long_decimal_to_decimal(long_res, res);

    if (long_res.bits[0] || long_res.bits[1] || long_res.bits[2]) {
      s21_set_exponent(res, res_power);
      setBit(res, 127, !(getSign(value_1) == getSign(value_2)));
    }
  }

  return result;
}
