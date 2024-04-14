#include "s21_tests.h"

START_TEST(s21_decimal_to_int1) {
  int n = 0, test = 0;
  s21_decimal d = {{123, 0, 0, 0}};
  setScale(&d, 3);
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 0);
  ck_assert_int_eq(test, n);
}
END_TEST

START_TEST(s21_decimal_to_int2) {
  int n = 0, test = 123;
  s21_decimal d = {{test, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 0);
  ck_assert_int_eq(test, n);
}
END_TEST

START_TEST(s21_decimal_to_int3) {
  int n = 0, test = -123;
  s21_decimal d = {{123, 0, 0, S21_MINUS}};
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 0);
  ck_assert_int_eq(test, n);
}
END_TEST

START_TEST(s21_decimal_to_int4) {
  int n = 0, test = INT32_MAX;
  s21_decimal d = {{test, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 0);
  ck_assert_int_eq(test, n);
}
END_TEST

START_TEST(s21_decimal_to_int5) {
  int n = 0, test = INT32_MIN;
  s21_decimal d = {{test, 0, 0, S21_MINUS}};
  setScale(&d, 10);
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 0);
  ck_assert_int_eq(test / pow(10, 10), n);
}
END_TEST

START_TEST(s21_decimal_to_int6) {
  int n = 0;
  s21_decimal d = {{S21_MAX_UINT, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 1);
}
END_TEST

START_TEST(s21_decimal_to_int7) {
  int n = 0;
  s21_decimal d = {{S21_MAX_UINT, S21_MAX_UINT, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 1);
}
END_TEST

START_TEST(s21_decimal_to_int8) {
  int n = 0;
  s21_decimal d = {{0x4DCF31C7, 0xA43B73EB, 0x0000000B, 0}};
  setScale(&d, 11);
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 0);
  ck_assert_int_eq(INT32_MAX, n);
}
END_TEST

START_TEST(s21_decimal_to_int9) {
  int n = 0;
  s21_decimal d = {{0x4DCF31C7, 0xA43B73EB, 0x0000000B, S21_MINUS}};
  setScale(&d, 11);
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 0);
  ck_assert_int_eq(-INT32_MAX, n);
}
END_TEST

START_TEST(s21_decimal_to_int10) {
  int n = 0;
  s21_decimal d = {{0x80000000, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(d, &n), 1);
}
END_TEST

START_TEST(s21_decimal_to_int11) {
  s21_decimal d = {{INT32_MAX, INT32_MAX, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(d, NULL), 1);
}
END_TEST

Suite *s21_decimal_to_int_suite(void) {
  Suite *s = suite_create("DECIMAL TO INT");
  TCase *tc_core = tcase_create("Core decimal to int");
  tcase_add_test(tc_core, s21_decimal_to_int1);
  tcase_add_test(tc_core, s21_decimal_to_int2);
  tcase_add_test(tc_core, s21_decimal_to_int3);
  tcase_add_test(tc_core, s21_decimal_to_int4);
  tcase_add_test(tc_core, s21_decimal_to_int5);
  tcase_add_test(tc_core, s21_decimal_to_int6);
  tcase_add_test(tc_core, s21_decimal_to_int7);
  tcase_add_test(tc_core, s21_decimal_to_int8);
  tcase_add_test(tc_core, s21_decimal_to_int9);
  tcase_add_test(tc_core, s21_decimal_to_int10);
  tcase_add_test(tc_core, s21_decimal_to_int11);
  suite_add_tcase(s, tc_core);
  return s;
}
