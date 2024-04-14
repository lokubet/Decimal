#ifndef S21_BIG_DECIMAL_H
#define S21_BIG_DECIMAL_H

#include "s21_decimal.h"

int s21_is_greater_or_equal_l(s21_extended_decimal a, s21_extended_decimal b);

int s21_is_less_l(s21_extended_decimal a, s21_extended_decimal b);

int s21_is_equal_l(s21_extended_decimal a, s21_extended_decimal b);

int s21_is_zero_l(s21_extended_decimal d);

void s21_normalization_l(s21_extended_decimal *a, s21_extended_decimal *b);

void s21_copy_l(s21_extended_decimal value, s21_extended_decimal *result);

void s21_remove_zeros_l(s21_extended_decimal *value);

int s21_add_l(s21_extended_decimal value_1, s21_extended_decimal value_2,
              s21_extended_decimal *result);

int s21_sub_l(s21_extended_decimal value_1, s21_extended_decimal value_2,
              s21_extended_decimal *result);

void alignmentScale_l(s21_extended_decimal *value_1,
                      s21_extended_decimal *value_2);

s21_extended_decimal *convert_l(s21_extended_decimal *value);

int s21_get_10_deg_l(s21_extended_decimal dst);

int getBit_l(s21_extended_decimal value, int bit);

int addBit_l(s21_extended_decimal value_1, s21_extended_decimal value_2,
             s21_extended_decimal *result);

s21_extended_decimal *setBit_l(s21_extended_decimal *value, int pos, int bit);

s21_extended_decimal *decreaseScale_l(s21_extended_decimal *value, int shift);

s21_extended_decimal *increaseScale_l(s21_extended_decimal *value, int shift);

s21_extended_decimal *setScale_l(s21_extended_decimal *value, int scale);

s21_extended_decimal *setSign_l(s21_extended_decimal *value, int bit);

s21_extended_decimal *leftShift_l(s21_extended_decimal *value, int shift);

int getBitLast_l(s21_extended_decimal value);

int getBitFirst_l(s21_extended_decimal value);

s21_extended_decimal *rightShift_l(s21_extended_decimal *value, int shift);

int s21_from_big_to_small(s21_extended_decimal big, s21_decimal *res,
                          int scale);

int s21_div10_l(s21_extended_decimal *result, int times);

void s21_mul_by_10_l(s21_extended_decimal *dst, int times);

s21_extended_decimal s21_from_d_to_big(s21_decimal v1);

int s21_is_even_l(s21_extended_decimal d);

void s21_banking_round_l(s21_extended_decimal d, s21_extended_decimal *res);

#endif