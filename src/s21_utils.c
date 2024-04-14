#include "s21_decimal.h"

int s21_get_nth_bit(int num, int n) {
  // n in [0, 31]
  return (num & (1 << n)) != 0;
}

int s21_get_nth_bit_of_decimal(s21_decimal *dst, int n) {
  // n in [0, 95]
  return s21_get_nth_bit(dst->bits[n / BITS_IN_INT], n % BITS_IN_INT);
}

void s21_make_zero_decimal(s21_decimal *result) {
  for (int i = 0; i < 4; ++i) {
    result->bits[i] = 0;
  }
}

void s21_make_zero_extended_decimal(s21_extended_decimal *result) {
  for (int i = 0; i < 7; ++i) {
    result->bits[i] = 0;
  }
}

void s21_remove_zeros(s21_decimal *value) {
  int last_num = 0, flag = 1;
  s21_decimal buf;
  s21_make_zero_decimal(&buf);
  while (flag) {
    s21_copy(*value, &buf);
    last_num = s21_div10(&buf, 1);
    if (last_num || buf.bits[3] == 0x80000000) {
      flag = 0;
    } else {
      s21_copy(buf, value);
      value->bits[3] -= 0x00010000;
    }
  }
  if (s21_is_zero(*value)) value->bits[3] = 0;
}

int s21_count_bits(unsigned long long num) {
  int count = 0;
  while (num > 0) {
    num /= 2;
    count++;
  }
  return count;
}

int s21_get_10_deg(s21_decimal *dst) {
  int num = dst->bits[3];
  // маска (11111111) 8 битов
  int mask = 0xFF << 16;
  // & оставляет биты, где маска имеет единицу, обнуляет остальные, затем сдвиг
  // на 16, чтобы число стало младшими 8 битами
  int ten_deg = (num & mask) >> 16;
  return ten_deg;
}

void s21_copy(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
}

int s21_div10(s21_decimal *result, int times) {
  int num = 0;
  unsigned long long big_num = 0;
  while (times > 0) {
    big_num = result->bits[2];
    for (int i = 2; i >= 0; i--) {
      if (i == 0) {
        num = big_num % 10;
        result->bits[i] = big_num / 10;
      } else {
        num = big_num % 10;
        result->bits[i] = big_num / 10;
        big_num = num * (4294967296) + result->bits[i - 1];
      }
    }
    times--;
  }
  return num;
}

int s21_is_zero(s21_decimal d) {
  int ret = 1;
  for (int i = 0; i < 3; ++i) {
    if (d.bits[i] != 0) {
      ret = 0;
    }
  }
  return ret;
}

void s21_normalization(s21_decimal *a, s21_decimal *b) {
  s21_decimal little_num, big_num;
  int exp_a = a->bits[3] << 1 >> 17, exp_b = b->bits[3] << 1 >> 17, exp_dif,
      flag = 0, part3 = 0;
  unsigned long long transfer = 0, new_num = 0, buf = 0, overflow = 0,
                     part2 = 0;
  exp_dif = abs(exp_a - exp_b);
  little_num.bits[3] = 0;
  big_num.bits[3] = 0;
  if (exp_a > exp_b) {
    s21_copy(*b, &little_num);
    s21_copy(*a, &big_num);
  } else {
    s21_copy(*a, &little_num);
    s21_copy(*b, &big_num);
  }
  for (int i = 0; i < 3; i++) {
    buf = little_num.bits[i];
    overflow = 0;
    for (int j = 0; j < exp_dif; j++) {
      new_num = buf * (unsigned long)10;
      buf *= 10;
      overflow *= 10;
      little_num.bits[i] *= 10;
      if (s21_count_bits(new_num) > 32) {
        transfer = new_num >> 32;
        if (s21_count_bits(transfer * 10) > 32 && !flag) {
          overflow = transfer;
          flag = 1;
        }
      }
      if (s21_count_bits(overflow) > 32) {
        part3 = overflow >> 32;
      }
      if (i == exp_dif - 1) {
        little_num.bits[i] += part2;
        part2 = transfer;
        if (i == 2) little_num.bits[i] += part3;
        if (s21_count_bits(transfer) > 32) part3 = transfer >> 32;
        transfer = 0;
      }
    }
  }
  if (exp_a > exp_b) {
    s21_copy(little_num, b);
    s21_copy(big_num, a);
  } else {
    s21_copy(little_num, a);
    s21_copy(big_num, b);
  }
}

s21_decimal *setSign(s21_decimal *value, int bit) {
  value->bits[3] =
      (bit) ? (value->bits[3] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
  return value;
}

int getSign(s21_decimal value) {
  int result = !!(value.bits[3] & (1u << 31));
  return result;
}

s21_decimal *convert(s21_decimal *value) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal add = {{1, 0, 0, 0}};
  for (int x = 0; x < 3; x += 1) value->bits[x] = ~value->bits[x];
  addBit(*value, add, &result);
  for (int x = 0; x < 3; x += 1) value->bits[x] = result.bits[x];
  setBit(value, 97, 1);
  return value;
}

s21_decimal *decreaseScale(s21_decimal *value, int shift) {
  for (int y = 0; y < shift; y += 1) {
    unsigned long long overflow = value->bits[2];
    for (int x = 2; x >= 0; x -= 1) {
      value->bits[x] = overflow / 10;
      overflow =
          (overflow % 10) * (S21_MAX_UINT + 1) + value->bits[x ? x - 1 : x];
    }
  }
  setScale(value, (getScale(*value) - shift));
  return value;
}

void alignmentScale(s21_decimal *value_1, s21_decimal *value_2) {
  if (getScale(*value_1) != getScale(*value_2)) {
    if (getScale(*value_1) < getScale(*value_2)) {
      alignmentScale(value_2, value_1);
    } else {
      int scaleLow = getScale(*value_2), scaleHigh = getScale(*value_1);
      for (; (scaleHigh - scaleLow) && !getBit(*value_2, 96); scaleLow += 1)
        increaseScale(value_2, 1);
      for (; scaleHigh - scaleLow; scaleHigh -= 1) {
        decreaseScale(value_1, scaleHigh - scaleLow);
        setScale(value_1, scaleLow);
      }
    }
  }
}

s21_decimal *increaseScale(s21_decimal *value, int shift) {
  if (getScale(*value) + shift < 29) {
    setScale(value, getScale(*value) + shift);
    s21_decimal auxValue_1 = *value, auxValue_2 = *value;
    if (addBit(*leftShift(&auxValue_1, 1), *leftShift(&auxValue_2, 3), value))
      setBit(value, 96, 1);
  }
  return value;
}

s21_decimal *leftShift(s21_decimal *value, int shift) {
  if (!(getBitLast(*value) + shift > 95)) {
    for (int y = 0; y < shift; y += 1) {
      int bitTransfer_1 = getBit(*value, 31);
      int bitTransfer_2 = getBit(*value, 63);
      for (int x = 0; x < 3; x += 1) value->bits[x] <<= 1;
      if (bitTransfer_1) setBit(value, 32, 1);
      if (bitTransfer_2) setBit(value, 64, 1);
    }
  }
  return value;
}

int addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int fres = 0, exp = 0;
  for (int i = 0; i < 96; i += 1) {
    int bitValue_1 = getBit(value_1, i), bitValue_2 = getBit(value_2, i);
    if (!bitValue_1 && !bitValue_2)
      exp ? setBit(result, i, (exp = 0) + 1) : setBit(result, i, 0);
    else if (bitValue_1 != bitValue_2)
      exp ? setBit(result, i, (exp = 1) - 1) : setBit(result, i, 1);
    else
      exp ? setBit(result, i, (exp = 1)) : setBit(result, i, (exp = 1) - 1);
    if (i == 95 && exp == 1 && !getBit(value_1, 97) && !getBit(value_2, 97))
      fres = 1;
  }
  return fres;
}

int getScale(s21_decimal value) {
  int result = (char)(value.bits[3] >> 16);
  return result;
}

s21_decimal *setScale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    int sign = getSign(*value);
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= scale << 16;
    sign ? setSign(value, 1) : value;
  }
  return value;
}

int getBit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

int getBitLast(s21_decimal value) {
  int bitLast = 95;
  for (; (bitLast >= 0) && (!getBit(value, bitLast));) bitLast -= 1;
  return bitLast;
}

s21_decimal *setBit(s21_decimal *value, int pos, int bit) {
  if (pos / 32 < 4 && bit)
    value->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    value->bits[pos / 32] &= ~(1u << (pos % 32));
  return value;
}

void s21_mul_by_10(s21_decimal *dst, int times) {
  s21_decimal val1, val2;
  // (num << 3) + (num << 1); // умножение на 10 в бинарном виде
  for (int i = 0; i < times; ++i) {
    s21_copy(*dst, &val1);
    s21_copy(*dst, &val2);
    leftShift(&val1, 3);
    leftShift(&val2, 1);
    s21_add(val1, val2, dst);
  }
}

unsigned int s21_getbit_long(s21_extended_decimal num, int bit) {
  int index = bit / 32;
  bit %= 32;
  return (num.bits[index] & 0b1 << bit) >> bit;
}

void s21_setbit_long(s21_extended_decimal *num, int bit,
                     const unsigned int set) {
  int index = bit / 32;
  bit %= 32;
  if (set)
    num->bits[index] = num->bits[index] | (0b1 << bit);
  else
    num->bits[index] = num->bits[index] & ~(0b1 << bit);
}

void s21_add_replace(s21_extended_decimal num1, s21_extended_decimal num2,
                     s21_extended_decimal *result, int i, unsigned int *temp) {
  int temp_result = s21_getbit_long(num1, i) + s21_getbit_long(num2, i) + *temp;
  if (temp_result == 3) {
    s21_setbit_long(result, i, 1);
    *temp = 1;
  } else if (temp_result == 2) {
    s21_setbit_long(result, i, 0);
    *temp = 1;
  } else if (temp_result == 1) {
    s21_setbit_long(result, i, 1);
    *temp = 0;
  } else if (!temp_result) {
    s21_setbit_long(result, i, 0);
    *temp = 0;
  }
}

int s21_get_exponent_long(s21_extended_decimal num) {
  int exponent = (num.bits[6] >> 16) & 0xFF;
  return exponent;
}

int s21_get_sign_long(s21_extended_decimal num) {
  int sign = (num.bits[6] & 0x80000000) ? 1 : 0;
  return sign;
}

void s21_multiply_by_ten_long(s21_extended_decimal *value) {
  unsigned long long carry = 0;

  for (int i = 0; i < 6; i++) {
    unsigned long long product =
        (unsigned long long)value->bits[i] * 10 + carry;
    value->bits[i] = (int)(product & 0xFFFFFFFF);
    carry = product >> 32;
  }
}

void s21_modulo_by_ten_long(s21_extended_decimal *value, int *remainder) {
  s21_extended_decimal temp = *value;
  s21_extended_decimal res = {0};
  s21_extended_decimal borrow = {0};
  s21_divide_by_ten_long(&temp);
  s21_multiply_by_ten_long(&temp);
  for (int i = 0; i < 6; i++) {
    unsigned long long intPart = (unsigned long long)value->bits[i] -
                                 (unsigned long long)temp.bits[i] -
                                 borrow.bits[i];
    if (value->bits[i] < temp.bits[i] || intPart >= 0x100000000ull) {
      borrow.bits[i] = 0x1;
    } else {
      borrow.bits[i] = 0x0;
    }

    res.bits[i] = (int)(intPart & 0xFFFFFFFF);
  }
  *remainder = res.bits[0];
}

void s21_set_exponent(s21_decimal *value, int new_exponent) {
  value->bits[3] &= 0xFF00FFFF;
  value->bits[3] |= (new_exponent & 0xFF) << 16;
}

int s21_get_exponent(s21_decimal num) {
  int exponent = (num.bits[3] >> 16) & 0xFF;
  return exponent;
}

void s21_set_sign_long(s21_extended_decimal *value, int sign) {
  s21_setbit_long(value, 223, sign);
}

void s21_set_exponent_long(s21_extended_decimal *value, int new_exponent) {
  value->bits[6] &= 0xFF00FFFF;
  value->bits[6] |= (new_exponent & 0xFF) << 16;
}

void s21_decimal_to_long_decimal(s21_decimal value,
                                 s21_extended_decimal *result) {
  int sign = getSign(value);
  s21_set_sign_long(result, sign);

  int exponent = s21_get_exponent(value);
  s21_set_exponent_long(result, exponent);

  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
}

void s21_normalize_long(s21_extended_decimal *num1,
                        s21_extended_decimal *num2) {
  int exponent1 = s21_get_exponent_long(*num1);
  int exponent2 = s21_get_exponent_long(*num2);
  int scale_diff = abs(exponent2 - exponent1);

  int sign1 = s21_get_sign_long(*num1);
  int sign2 = s21_get_sign_long(*num2);
  int new_sign = (sign1 == sign2) ? sign1 : 0;
  s21_setbit_long(num1, 223, new_sign);
  s21_setbit_long(num2, 223, new_sign);

  if (exponent1 >= exponent2) {
    for (int i = 0; i < scale_diff; i++) {
      unsigned long long carry = 0;
      for (int j = 5; j >= 0; j--) {
        unsigned long long intPart = (unsigned long long)num2->bits[j] * 10;
        carry = (unsigned int)(intPart >> 32);
        num2->bits[j] = (unsigned int)intPart;
        // printf("carry: %lld, j: %d\n", carry, j);
        num2->bits[j + 1] += carry;
      }
      num2->bits[6] = (num2->bits[6] & 0xFF00FFFF) | (((exponent1)&0xFF) << 16);
    }
  } else if (exponent1 < exponent2) {
    for (int i = 0; i < scale_diff; i++) {
      unsigned long long carry = 0;
      for (int j = 5; j >= 0; j--) {
        unsigned long long intPart = (unsigned long long)num1->bits[j] * 10;
        carry = (unsigned int)(intPart >> 32);
        num1->bits[j] = (unsigned int)intPart;
        num1->bits[j + 1] += carry;
      }
      num1->bits[6] = (num1->bits[6] & 0xFF00FFFF) | (((exponent2)&0xFF) << 16);
    }
  }

  s21_setbit_long(num1, 223, sign1);
  s21_setbit_long(num2, 223, sign2);
}

void s21_shift_left_long(s21_extended_decimal *value, int number) {
  for (int i = 0; i < number; i++) {
    for (int j = 191; j > 0 + i; j--) {
      unsigned int temp = s21_getbit_long(*value, j - 1);
      s21_setbit_long(value, j, temp);
    }
    s21_setbit_long(value, i, 0);
  }
}

void s21_divide_by_ten_long(s21_extended_decimal *value) {
  unsigned long long buf = 0;
  unsigned long long ost = 0;
  for (int i = 5; i >= 0; i--) {
    buf += value->bits[i];
    ost = buf % 10;
    value->bits[i] = (int)(buf / 10);
    buf = ost << 32;
  }
  if (ost > 4) {
    value->bits[0] += 1;
  }
}

void s21_sum_full(s21_extended_decimal num1, s21_extended_decimal num2,
                  s21_extended_decimal *result, unsigned int *temp) {
  for (int i = 0; i <= 191; i++) {
    s21_add_replace(num1, num2, result, i, temp);
  }
}

void s21_long_decimal_to_decimal(s21_extended_decimal value,
                                 s21_decimal *result) {
  s21_init_result(result);
  int exponent = s21_get_exponent_long(value);
  int highest_bit_pos = s21_get_highest_bit_pos_long(value);
  s21_extended_decimal temp = value;
  s21_decimal decimal_one = {{0x00000001, 0, 0, 0}};

  if (highest_bit_pos > 95) {
    // printf("long decimal case\n");
    int scale_diff = highest_bit_pos - 95;

    while (highest_bit_pos - 95 >= 0) {
      // s21_print_long_decimal(value);
      s21_divide_by_ten_long(&value);
      exponent -= 1;
      highest_bit_pos = s21_get_highest_bit_pos_long(value);
    }

    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];

    for (int j = 0; j < scale_diff - 1; j++) {
      s21_divide_by_ten_long(&temp);
    }
    int lastnum = 0;
    s21_modulo_by_ten_long(&temp, &lastnum);
    if (lastnum >= 5) {
      s21_add(*result, decimal_one, result);
    }
  } else {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
  }
  int sign = s21_get_sign_long(value);
  setSign(result, sign);
  s21_set_exponent(result, exponent);
}

int s21_get_highest_bit_pos_long(s21_extended_decimal value) {
  int bit_pos = -1;

  for (int i = 0; i < 192; i++) {
    if ((s21_getbit_long(value, (191 - i)) == 1) && (bit_pos == -1)) {
      bit_pos = (191 - i);
    }
  }

  return bit_pos;
}

void s21_init_result(s21_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
}
