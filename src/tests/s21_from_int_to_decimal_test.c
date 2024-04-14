#include "s21_tests.h"

START_TEST(int_to_decimal_test1) {
  s21_decimal s21_d, d = {.bits = {INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(s21_from_int_to_decimal(INT_MAX, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(int_to_decimal_test2) {
  s21_decimal s21_d, d = {.bits = {INT_MIN, 0, 0, S21_MINUS}};
  ck_assert_int_eq(s21_from_int_to_decimal(INT_MIN, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(int_to_decimal_test3) {
  int t = 0;
  s21_decimal s21_d, d = {.bits = {t, 0, 0, 0}};
  ck_assert_int_eq(s21_from_int_to_decimal(t, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(int_to_decimal_test4) {
  ck_assert_int_eq(s21_from_int_to_decimal(1, NULL), 1);
}
END_TEST

Suite *s21_int_to_decimal_suite(void) {
  Suite *s = suite_create("INT TO DECIMAL");
  TCase *tc_core = tcase_create("Core int to decimal");
  tcase_add_test(tc_core, int_to_decimal_test1);
  tcase_add_test(tc_core, int_to_decimal_test2);
  tcase_add_test(tc_core, int_to_decimal_test3);
  tcase_add_test(tc_core, int_to_decimal_test4);
  suite_add_tcase(s, tc_core);
  return s;
}
