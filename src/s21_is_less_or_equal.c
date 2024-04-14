#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int flag = 0;
  if (s21_is_less(a, b) || s21_is_equal(a, b)) {
    flag = 1;
  }
  return flag;
}