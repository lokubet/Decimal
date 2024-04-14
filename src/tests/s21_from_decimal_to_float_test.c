#include "s21_tests.h"

START_TEST(decimal_to_float_test1) {
  float s21_f = 0, f = 0.123f;
  s21_decimal d = {.bits = {123, 0, 0, 0}};
  d.bits[3] |= (3 << 16);
  ck_assert_int_eq(s21_from_decimal_to_float(d, &s21_f), 0);
  ck_assert_float_eq(s21_f, f);
}
END_TEST

START_TEST(decimal_to_float_test2) {
  s21_decimal d = {.bits = {1234, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_float(d, NULL), 1);
}
END_TEST

START_TEST(decimal_to_float_test3) {
  float s21_f = 0, f = 0.0f;
  s21_decimal d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_float(d, &s21_f), 0);
  ck_assert_float_eq(s21_f, f);
}
END_TEST

START_TEST(decimal_to_float_test4) {
  float s21_f = 0, f = -123.0f;
  s21_decimal d = {.bits = {123, 0, 0, S21_MINUS}};
  ck_assert_int_eq(s21_from_decimal_to_float(d, &s21_f), 0);
  ck_assert_float_eq(s21_f, f);
}
END_TEST

START_TEST(decimal_to_float_test5) {
  float s21_f = 0, f = -1234567.123f;
  s21_decimal d = {.bits = {1234567123, 0, 0, 0x80030000}};
  ck_assert_int_eq(s21_from_decimal_to_float(d, &s21_f), 0);
  ck_assert_float_eq(s21_f, f);
}
END_TEST

START_TEST(decimal_to_float_test6) {
  float s21_f = 0, f = 1230000.0f;
  s21_decimal d = {.bits = {1230000, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_float(d, &s21_f), 0);
  ck_assert_float_eq(s21_f, f);
}
END_TEST

Suite *s21_decimal_to_float_suite(void) {
  Suite *s = suite_create("DECIMAL TO FLOAT");
  TCase *tc_core = tcase_create("Core decimal to float");
  tcase_add_test(tc_core, decimal_to_float_test1);
  tcase_add_test(tc_core, decimal_to_float_test2);
  tcase_add_test(tc_core, decimal_to_float_test3);
  tcase_add_test(tc_core, decimal_to_float_test4);
  tcase_add_test(tc_core, decimal_to_float_test5);
  tcase_add_test(tc_core, decimal_to_float_test6);
  suite_add_tcase(s, tc_core);
  return s;
}