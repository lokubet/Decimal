#include "s21_tests.h"

START_TEST(negate_test0) {
  s21_decimal s21_d, d_val = {.bits = {1, 2, 3, 40 << 16}};
  ck_assert_int_eq(s21_negate(d_val, &s21_d), 1);
}
END_TEST

START_TEST(negate_test1) {
  s21_decimal d_val = {.bits = {S21_MINUS, 0, 0, 0}};
  ck_assert_int_eq(s21_negate(d_val, NULL), 1);
}
END_TEST

START_TEST(negate_test2) {
  s21_decimal s21_d, d_val = {.bits = {0, 0, 0, 0}},
                     d = {.bits = {0, 0, 0, S21_MINUS}};
  ck_assert_int_eq(s21_negate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(negate_test3) {
  s21_decimal s21_d, d_val = {.bits = {0, 0, 0, S21_MINUS}},
                     d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_negate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(negate_test4) {
  s21_decimal s21_d, d_val = {.bits = {0, 150, 20, 0}},
                     d = {.bits = {0, 150, 20, S21_MINUS}};
  ck_assert_int_eq(s21_negate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(negate_test5) {
  s21_decimal s21_d, d_val = {.bits = {0xFFFFFFF, 0xFFFFFFF, 0xFFFFFFF, 0}},
                     d = {.bits = {0xFFFFFFF, 0xFFFFFFF, 0xFFFFFFF, S21_MINUS}};
  ck_assert_int_eq(s21_negate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s = suite_create("NEGATE");
  TCase *tc_core = tcase_create("Negate");
  tcase_add_test(tc_core, negate_test0);
  tcase_add_test(tc_core, negate_test1);
  tcase_add_test(tc_core, negate_test2);
  tcase_add_test(tc_core, negate_test3);
  tcase_add_test(tc_core, negate_test4);
  tcase_add_test(tc_core, negate_test5);
  suite_add_tcase(s, tc_core);
  return s;
}