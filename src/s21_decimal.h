#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BITS_IN_INT 32
#define BITS 96
#define S21_MAX_UINT 4294967295

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];  // 6 * 32 = 192 bits, 1 int for sign
} s21_extended_decimal;

#include "s21_big_decimal_stuff.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);

int s21_is_less_or_equal(s21_decimal, s21_decimal);

int s21_is_greater(s21_decimal, s21_decimal);

int s21_is_greater_or_equal(s21_decimal, s21_decimal);

int s21_is_equal(s21_decimal, s21_decimal);

int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);

int s21_from_float_to_decimal(float src, s21_decimal *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);

int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);

int s21_round(s21_decimal value, s21_decimal *result);

int s21_truncate(s21_decimal value, s21_decimal *result);

int s21_negate(s21_decimal value, s21_decimal *result);

// UTILS

int s21_get_nth_bit(int num, int n);  // Get nth bit from integer num

int s21_get_nth_bit_of_decimal(s21_decimal *dst, int n);

void s21_make_zero_decimal(s21_decimal *result);

void s21_make_zero_extended_decimal(s21_extended_decimal *result);

void s21_remove_zeros(s21_decimal *value);

int s21_count_bits(unsigned long long num);

int s21_get_10_deg(s21_decimal *dst);

void s21_set_nth_bit_of_decimal(s21_decimal *dst, int n);

void s21_copy(s21_decimal value, s21_decimal *result);

int s21_div10(s21_decimal *result, int times);

void s21_set_nth_bit_of_decimal_to_0(s21_decimal *dst, int n);

int s21_is_zero(s21_decimal d);

void s21_decimal_shift_left(s21_decimal *dec);

void s21_decimal_shift_right(s21_decimal *dec);

void s21_normalization(s21_decimal *value_1, s21_decimal *value_2);

int getSign(s21_decimal value);

s21_decimal *setSign(s21_decimal *value, int bit);

s21_decimal *convert(s21_decimal *value);

s21_decimal *decreaseScale(s21_decimal *value, int shift);

void alignmentScale(s21_decimal *value_1, s21_decimal *value_2);

s21_decimal *setScale(s21_decimal *value, int scale);

int getScale(s21_decimal value);

int addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

s21_decimal *increaseScale(s21_decimal *value, int shift);

s21_decimal *leftShift(s21_decimal *value, int shift);

int getBit(s21_decimal value, int bit);

int getBitLast(s21_decimal value);

s21_decimal *setBit(s21_decimal *value, int pos, int bit);

void s21_mul_by_10(s21_decimal *dst, int times);

void s21_set_exponent(s21_decimal *value, int new_exponent);

int s21_get_exponent(s21_decimal num);

void s21_set_sign_long(s21_extended_decimal *value, int sign);

void s21_set_exponent_long(s21_extended_decimal *value, int new_exponent);

void s21_decimal_to_long_decimal(s21_decimal value,
                                 s21_extended_decimal *result);

void s21_normalize_long(s21_extended_decimal *num1, s21_extended_decimal *num2);

void s21_shift_left_long(s21_extended_decimal *value, int number);

void s21_divide_by_ten_long(s21_extended_decimal *value);

void s21_long_decimal_to_decimal(s21_extended_decimal value,
                                 s21_decimal *result);

void s21_sum_full(s21_extended_decimal num1, s21_extended_decimal num2,
                  s21_extended_decimal *result, unsigned int *temp);

unsigned int s21_getbit_long(s21_extended_decimal num, int bit);

void s21_setbit_long(s21_extended_decimal *num, int bit,
                     const unsigned int set);

void s21_add_replace(s21_extended_decimal num1, s21_extended_decimal num2,
                     s21_extended_decimal *result, int i, unsigned int *temp);

int s21_get_exponent_long(s21_extended_decimal num);

int s21_get_sign_long(s21_extended_decimal num);

void s21_multiply_by_ten_long(s21_extended_decimal *value);

void s21_modulo_by_ten_long(s21_extended_decimal *value, int *remainder);

int s21_get_highest_bit_pos_long(s21_extended_decimal value);

void s21_init_result(s21_decimal *result);

#endif
