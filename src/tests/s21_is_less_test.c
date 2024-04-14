#include "s21_tests.h"

START_TEST(is_less_test0) {
  s21_decimal d_val = {.bits = {0, 0, 0, 0}}, d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test1) {
  s21_decimal d_val = {.bits = {0, 0, 0, 0x00030000}},
              d = {.bits = {0, 0, 0, 0x00010000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test2) {
  s21_decimal d_val = {.bits = {0, 0, 0, 0x800A0000}},
              d = {.bits = {0, 0, 0, 0x00030000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test3) {
  s21_decimal d_val = {.bits = {1, 0, 0, 0}}, d = {.bits = {1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test4) {
  s21_decimal d_val = {.bits = {1, 0, 0, 0x80000000}},
              d = {.bits = {1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test5) {
  s21_decimal d_val = {.bits = {0x0000000C, 0x00000000, 0x00000000,
                                0x80010000}},
              d = {.bits = {0x00000070, 0x00000000, 0x00000000, 0x80020000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 1);
}
END_TEST

START_TEST(is_less_test6) {
  s21_decimal d_val = {.bits = {0x000000F3, 0x00000000, 0x00000000,
                                0x00020000}},
              d = {.bits = {0x000000F4, 0x00000000, 0x00000000, 0x00030000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test7) {
  s21_decimal d_val = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x00000000}},
              d = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 1);
}
END_TEST

START_TEST(is_less_test8) {
  s21_decimal d_val = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x00000000}},
              d = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test9) {
  s21_decimal d_val = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x80000000}},
              d = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test10) {
  s21_decimal d_val = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x80000000}},
              d = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 1);
}
END_TEST

START_TEST(is_less_test11) {
  s21_decimal d_val = {.bits = {0x0000009A, 0x00000000, 0x00000000,
                                0x00000000}},
              d = {.bits = {0x00003C28, 0x00000000, 0x00000000, 0x00020000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

START_TEST(is_less_test12) {
  s21_decimal d_val = {.bits = {0x0000009A, 0x00000000, 0x00000000,
                                0x80000000}},
              d = {.bits = {0x00003C28, 0x00000000, 0x00000000, 0x00020000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 1);
}
END_TEST

START_TEST(is_less_test13) {
  s21_decimal d_val = {.bits = {0x0000009A, 0x00000000, 0x00000000,
                                0x00000000}},
              d = {.bits = {0x00003C28, 0x00000000, 0x00000000, 0x80020000}};
  ck_assert_int_eq(s21_is_less(d_val, d), 0);
}
END_TEST

Suite *s21_is_less_suite(void) {
  Suite *s = suite_create("IS_LESS");
  TCase *tc_core = tcase_create("Is_less");
  tcase_add_test(tc_core, is_less_test0);
  tcase_add_test(tc_core, is_less_test1);
  tcase_add_test(tc_core, is_less_test2);
  tcase_add_test(tc_core, is_less_test3);
  tcase_add_test(tc_core, is_less_test4);
  tcase_add_test(tc_core, is_less_test5);
  tcase_add_test(tc_core, is_less_test6);
  tcase_add_test(tc_core, is_less_test7);
  tcase_add_test(tc_core, is_less_test8);
  tcase_add_test(tc_core, is_less_test9);
  tcase_add_test(tc_core, is_less_test10);
  tcase_add_test(tc_core, is_less_test11);
  tcase_add_test(tc_core, is_less_test12);
  tcase_add_test(tc_core, is_less_test13);
  suite_add_tcase(s, tc_core);
  return s;
}