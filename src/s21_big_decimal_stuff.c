#include "s21_decimal.h"

int s21_is_greater_or_equal_l(s21_extended_decimal a, s21_extended_decimal b) {
  int flag = 0;
  if (!s21_is_less_l(a, b)) {
    flag = 1;
  }
  return flag;
}

int s21_is_less_l(s21_extended_decimal a, s21_extended_decimal b) {
  int flag = 0, sign_bit_a = s21_get_nth_bit(a.bits[6], 31),
      sign_bit_b = s21_get_nth_bit(b.bits[6], 31);
  if (s21_is_equal_l(a, b)) {
    flag = 0;
  } else if ((sign_bit_a) && (sign_bit_b == 0)) {
    flag = 1;
  } else if ((sign_bit_a == 0) && (sign_bit_b)) {
    flag = 0;
  } else {
    a.bits[6] &= 0b01111111111111111111111111111111;
    b.bits[6] &= 0b01111111111111111111111111111111;
    s21_normalization_l(&a, &b);
    for (int i = 5; i >= 0; i--) {
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

int s21_is_equal_l(s21_extended_decimal a, s21_extended_decimal b) {
  int flag = 1;
  if (s21_is_zero_l(a) && s21_is_zero_l(b)) {
    flag = 1;
  } else if (s21_get_nth_bit(a.bits[6], 31) != s21_get_nth_bit(b.bits[6], 31)) {
    flag = 0;
  } else {
    s21_remove_zeros_l(&a);
    s21_remove_zeros_l(&b);
    a.bits[6] &= 0x01111111;
    b.bits[6] &= 0x01111111;
    s21_normalization_l(&a, &b);
    for (int i = 0; i < 7; i++) {
      if (a.bits[i] != b.bits[i]) {
        flag = 0;
      }
    }
  }
  return flag;
}

int s21_is_zero_l(s21_extended_decimal d) {
  int ret = 1;
  for (int i = 0; ret == 1 && i < 6; ++i) {
    if (d.bits[i] != 0) {
      ret = 0;
    }
  }
  return ret;
}

void s21_normalization_l(s21_extended_decimal *a, s21_extended_decimal *b) {
  s21_extended_decimal little_num, big_num;
  int exp_a = a->bits[6] << 1 >> 17, exp_b = b->bits[6] << 1 >> 17, exp_dif,
      flag = 0, part3 = 0;
  unsigned long long transfer = 0, new_num = 0, buf = 0, overflow = 0,
                     part2 = 0;
  exp_dif = abs(exp_a - exp_b);
  little_num.bits[6] = 0;
  big_num.bits[6] = 0;
  if (exp_a > exp_b) {
    s21_copy_l(*b, &little_num);
    s21_copy_l(*a, &big_num);
  } else {
    s21_copy_l(*a, &little_num);
    s21_copy_l(*b, &big_num);
  }
  for (int i = 0; i < 6; i++) {
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
    s21_copy_l(little_num, b);
    s21_copy_l(big_num, a);
  } else {
    s21_copy_l(little_num, a);
    s21_copy_l(big_num, b);
  }
}

void s21_copy_l(s21_extended_decimal value, s21_extended_decimal *result) {
  for (int i = 0; i < 7; i++) {
    result->bits[i] = value.bits[i];
  }
}

void s21_remove_zeros_l(s21_extended_decimal *value) {
  int last_num = 0, flag = 1;
  s21_extended_decimal buf;
  s21_make_zero_extended_decimal(&buf);
  while (flag) {
    s21_copy_l(*value, &buf);
    last_num = s21_div10_l(&buf, 1);
    if (last_num || buf.bits[6] == 0x80000000) {
      flag = 0;
    } else {
      s21_copy_l(buf, value);
      value->bits[6] -= 0x00010000;
    }
  }
  if (s21_is_zero_l(*value)) value->bits[6] = 0;
}

int s21_add_l(s21_extended_decimal value_1, s21_extended_decimal value_2,
              s21_extended_decimal *result) {
  int status = 0, valueSign_1 = s21_get_nth_bit(value_1.bits[6], 31),
      valueSign_2 = s21_get_nth_bit(value_2.bits[6], 31);
  for (int x = 0; x < 8; x += 1) result->bits[x] = 0;
  if (valueSign_1 == valueSign_2) {
    alignmentScale_l(&value_1, &value_2);
    if (addBit_l(value_1, value_2, result)) {
      if ((!s21_get_10_deg_l(value_1) || !s21_get_10_deg_l(value_2)) &&
          !valueSign_1) {
        status = 1;
      } else if ((!s21_get_10_deg_l(value_1) || !s21_get_10_deg_l(value_2)) &&
                 valueSign_1) {
        status = 2;
      } else if (s21_get_10_deg_l(value_1) > 0 &&
                 s21_get_10_deg_l(value_2) > 0) {
        setScale_l(decreaseScale_l(&value_1, 1), s21_get_10_deg_l(value_1) - 1);
        setScale_l(decreaseScale_l(&value_2, 1), s21_get_10_deg_l(value_2) - 1);
        status = s21_add_l(value_1, value_2, result);
      }
    } else {
      setScale_l(setSign_l(result, valueSign_1), s21_get_10_deg_l(value_1));
    }
  } else if (valueSign_1 && !valueSign_2) {
    status = s21_sub_l(value_2, *setSign_l(&value_1, 0), result);
  } else if (!valueSign_1 && valueSign_2) {
    status = s21_sub_l(value_1, *setSign_l(&value_2, 0), result);
  }
  return status;
}

int s21_sub_l(s21_extended_decimal value_1, s21_extended_decimal value_2,
              s21_extended_decimal *result) {
  int status = 0, valueSign_1 = s21_get_nth_bit(value_1.bits[6], 31),
      valueSign_2 = s21_get_nth_bit(value_2.bits[6], 31);
  for (int x = 0; x < 8; x += 1) result->bits[x] = 0;
  if (valueSign_1 != valueSign_2) {
    status =
        s21_add_l(*setSign_l(&value_1, 0), *setSign_l(&value_2, 0), result);
    status = status ? (valueSign_1 ? 2 : 1) : status;
    setSign_l(result, valueSign_1);
  } else {
    alignmentScale_l(&value_1, &value_2);
    if (!s21_is_equal_l(value_1, value_2)) {
      setSign_l(&value_1, 0);
      setSign_l(&value_2, 0);
      if (s21_is_less_l(value_1, value_2)) {
        status = s21_add_l(*convert_l(&value_1), value_2, result);
        setSign_l(result, !valueSign_2);
      } else {
        status = s21_add_l(*convert_l(&value_2), value_1, result);
        setSign_l(result, valueSign_1);
      }
    }
  }
  return status;
}

void alignmentScale_l(s21_extended_decimal *value_1,
                      s21_extended_decimal *value_2) {
  if (s21_get_10_deg_l(*value_1) != s21_get_10_deg_l(*value_2)) {
    if (s21_get_10_deg_l(*value_1) < s21_get_10_deg_l(*value_2)) {
      alignmentScale_l(value_2, value_1);
    } else {
      int scaleLow = s21_get_10_deg_l(*value_2),
          scaleHigh = s21_get_10_deg_l(*value_1);
      for (; (scaleHigh - scaleLow) && !getBit_l(*value_2, 191); scaleLow += 1)
        increaseScale_l(value_2, 1);
      for (; scaleHigh - scaleLow; scaleHigh -= 1) {
        decreaseScale_l(value_1, scaleHigh - scaleLow);
        setScale_l(value_1, scaleLow);
      }
    }
  }
}

s21_extended_decimal *convert_l(s21_extended_decimal *value) {
  s21_extended_decimal result = {{0, 0, 0, 0, 0, 0, 0}};
  s21_extended_decimal add = {{1, 0, 0, 0, 0, 0, 0}};
  for (int x = 0; x < 7; x += 1) value->bits[x] = ~value->bits[x];
  addBit_l(*value, add, &result);
  for (int x = 0; x < 7; x += 1) value->bits[x] = result.bits[x];
  setBit_l(value, 193, 1);
  return value;
}

int s21_get_10_deg_l(s21_extended_decimal dst) {
  int num = dst.bits[6];
  // маска (11111111) 8 битов
  int mask = 0xFF << 16;
  // & оставляет биты, где маска имеет единицу, обнуляет остальные, затем сдвиг
  // на 16, чтобы число стало младшими 8 битами
  int ten_deg = (num & mask) >> 16;
  return ten_deg;
}

int getBit_l(s21_extended_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

int addBit_l(s21_extended_decimal value_1, s21_extended_decimal value_2,
             s21_extended_decimal *result) {
  int fres = 0, exp = 0;
  for (int i = 0; i < 192; i += 1) {
    int bitValue_1 = getBit_l(value_1, i), bitValue_2 = getBit_l(value_2, i);
    if (!bitValue_1 && !bitValue_2)
      exp ? setBit_l(result, i, (exp = 0) + 1) : setBit_l(result, i, 0);
    else if (bitValue_1 != bitValue_2)
      exp ? setBit_l(result, i, (exp = 1) - 1) : setBit_l(result, i, 1);
    else
      exp ? setBit_l(result, i, (exp = 1)) : setBit_l(result, i, (exp = 1) - 1);
    if (i == 191 && exp == 1 && !getBit_l(value_1, 97) &&
        !getBit_l(value_2, 97))
      fres = 1;
  }
  return fres;
}

s21_extended_decimal *setBit_l(s21_extended_decimal *value, int pos, int bit) {
  if (pos / 32 < 8 && bit)
    value->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 8 && !bit)
    value->bits[pos / 32] &= ~(1u << (pos % 32));
  return value;
}

s21_extended_decimal *decreaseScale_l(s21_extended_decimal *value, int shift) {
  for (int y = 0; y < shift; y += 1) {
    unsigned long long overflow = value->bits[5];
    for (int x = 5; x >= 0; x -= 1) {
      value->bits[x] = overflow / 10;
      overflow =
          (overflow % 10) * (S21_MAX_UINT + 1) + value->bits[x ? x - 1 : x];
    }
  }
  setScale_l(value, (s21_get_10_deg_l(*value) - shift));
  return value;
}

s21_extended_decimal *increaseScale_l(s21_extended_decimal *value, int shift) {
  if (s21_get_10_deg_l(*value) + shift < 29) {
    setScale_l(value, s21_get_10_deg_l(*value) + shift);
    s21_extended_decimal auxValue_1 = *value, auxValue_2 = *value;
    if (addBit_l(*leftShift_l(&auxValue_1, 1), *leftShift_l(&auxValue_2, 3),
                 value))
      setBit_l(value, 192, 1);
  }
  return value;
}

s21_extended_decimal *setScale_l(s21_extended_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    int sign = s21_get_nth_bit(value->bits[6], 31);
    value->bits[6] &= ~(0xFF << 16);
    value->bits[6] |= scale << 16;
    sign ? setSign_l(value, 1) : value;
  }
  return value;
}

s21_extended_decimal *setSign_l(s21_extended_decimal *value, int bit) {
  value->bits[6] =
      (bit) ? (value->bits[6] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
  return value;
}

s21_extended_decimal *leftShift_l(s21_extended_decimal *value, int shift) {
  if (!(getBitLast_l(*value) + shift > 191)) {
    for (int y = 0; y < shift; y += 1) {
      int bitTransfer_1 = getBit_l(*value, 31);
      int bitTransfer_2 = getBit_l(*value, 63);
      int bitTransfer_3 = getBit_l(*value, 95);
      int bitTransfer_4 = getBit_l(*value, 127);
      int bitTransfer_5 = getBit_l(*value, 159);
      for (int x = 0; x < 7; x += 1) value->bits[x] <<= 1;
      if (bitTransfer_1) setBit_l(value, 32, 1);
      if (bitTransfer_2) setBit_l(value, 64, 1);
      if (bitTransfer_3) setBit_l(value, 96, 1);
      if (bitTransfer_4) setBit_l(value, 128, 1);
      if (bitTransfer_5) setBit_l(value, 160, 1);
    }
  }
  return value;
}

s21_extended_decimal *rightShift_l(s21_extended_decimal *value, int shift) {
  if (!(getBitFirst_l(*value) - shift < 0)) {
    for (int y = 0; y < shift; y += 1) {
      int bitTransfer_1 = getBit_l(*value, 32);
      int bitTransfer_2 = getBit_l(*value, 64);
      int bitTransfer_3 = getBit_l(*value, 96);
      int bitTransfer_4 = getBit_l(*value, 128);
      int bitTransfer_5 = getBit_l(*value, 160);
      for (int x = 6; x >= 0; x -= 1) value->bits[x] >>= 1;
      if (bitTransfer_1) setBit_l(value, 31, 1);
      if (bitTransfer_2) setBit_l(value, 63, 1);
      if (bitTransfer_3) setBit_l(value, 95, 1);
      if (bitTransfer_4) setBit_l(value, 127, 1);
      if (bitTransfer_5) setBit_l(value, 159, 1);
    }
  }
  return value;
}

int getBitLast_l(s21_extended_decimal value) {
  int bitLast = 191;
  for (; (bitLast >= 0) && (!getBit_l(value, bitLast));) bitLast -= 1;
  return bitLast;
}

int getBitFirst_l(s21_extended_decimal value) {
  int bitFirst = 0;
  for (; (bitFirst < 192) && (!getBit_l(value, bitFirst));) bitFirst += 1;
  return bitFirst;
}

int s21_is_overflow(s21_extended_decimal big) {
  int ret = 0;
  for (int i = 3; ret == 0 && i < 6; ++i) {
    if (big.bits[i] != 0) ret = 1;
  }
  return ret;
}

int s21_from_big_to_small(s21_extended_decimal big, s21_decimal *res,
                          int scale) {
  int ret = 0;
  big.bits[6] = 0;
  while (s21_is_overflow(big) && scale > 0) {
    s21_div10_l(&big, 1);
    --scale;
  }
  if (s21_is_overflow(big)) ret = 1;
  if (ret == 0) {
    setScale_l(&big, scale);
    if (scale == 28) s21_banking_round_l(big, &big);
    for (int i = 0; i < 3; ++i) {
      res->bits[i] = big.bits[i];
    }
    res->bits[3] = big.bits[6];
  }
  return ret;
}

int s21_div10_l(s21_extended_decimal *result, int times) {
  int num = 0;
  unsigned long long big_num = 0;
  while (times > 0) {
    big_num = result->bits[5];
    for (int i = 5; i >= 0; i--) {
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

void s21_mul_by_10_l(s21_extended_decimal *dst, int times) {
  s21_extended_decimal val1, val2;
  // (num << 3) + (num << 1); // умножение на 10 в бинарном виде
  for (int i = 0; i < times; ++i) {
    s21_copy_l(*dst, &val1);
    s21_copy_l(*dst, &val2);
    leftShift_l(&val1, 3);
    leftShift_l(&val2, 1);
    s21_add_l(val1, val2, dst);
  }
}

s21_extended_decimal s21_from_d_to_big(s21_decimal v1) {
  s21_extended_decimal res;
  s21_make_zero_extended_decimal(&res);
  for (int i = 0; i < 3; ++i) {
    res.bits[i] = v1.bits[i];
  }
  res.bits[6] = v1.bits[3];
  return res;
}

int s21_is_even_l(s21_extended_decimal d) {
  int ret = 0;
  s21_extended_decimal d2 = d;
  s21_extended_decimal t = *rightShift_l(&d2, 1);
  leftShift_l(&t, 1);
  if (s21_is_equal_l(d, t)) {
    ret = 1;
  }
  return ret;
}

void s21_banking_round_l(s21_extended_decimal d, s21_extended_decimal *res) {
  s21_extended_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
  s21_extended_decimal tmp;
  s21_copy_l(d, &tmp);
  int remainder = s21_div10_l(&tmp, 1);
  int scale = s21_get_10_deg_l(d);
  setScale_l(&one, scale - 1);
  if (remainder == 5) {
    if (s21_is_even_l(tmp)) {
      *res = d;
    } else {
      setScale_l(&tmp, scale - 1);
      s21_add_l(tmp, one, res);
    }
  } else if (remainder > 5) {
    setScale_l(&tmp, scale - 1);
    s21_add_l(tmp, one, res);
  } else {
    *res = d;
  }
}
