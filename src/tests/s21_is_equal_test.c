#include "s21_tests.h"

START_TEST(is_equal_test0) {
  s21_decimal d_val = {.bits = {0, 0, 0, 0}}, d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test1) {
  s21_decimal d_val = {.bits = {0, 0, 0, 0x00030000}},
              d = {.bits = {0, 0, 0, 0x00010000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test2) {
  s21_decimal d_val = {.bits = {0, 0, 0, 0x800A0000}},
              d = {.bits = {0, 0, 0, 0x00030000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test3) {
  s21_decimal d_val = {.bits = {1, 0, 0, 0}}, d = {.bits = {1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test4) {
  s21_decimal d_val = {.bits = {1, 0, 0, 0x80000000}},
              d = {.bits = {1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test5) {
  s21_decimal d_val = {.bits = {0x0000000C, 0x00000000, 0x00000000,
                                0x80010000}},
              d = {.bits = {0x00000070, 0x00000000, 0x00000000, 0x80020000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test6) {
  s21_decimal d_val = {.bits = {0x000000F3, 0x00000000, 0x00000000,
                                0x00020000}},
              d = {.bits = {0x000000F4, 0x00000000, 0x00000000, 0x00030000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test7) {
  s21_decimal d_val = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x00000000}},
              d = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test8) {
  s21_decimal d_val = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x00000000}},
              d = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test9) {
  s21_decimal d_val = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x80000000}},
              d = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test10) {
  s21_decimal d_val = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x80000000}},
              d = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test11) {
  s21_decimal d_val = {.bits = {0x0000009A, 0x00000000, 0x00000000,
                                0x00000000}},
              d = {.bits = {0x00003C28, 0x00000000, 0x00000000, 0x00020000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test12) {
  s21_decimal d_val = {.bits = {0x0000009A, 0x00000000, 0x00000000,
                                0x80000000}},
              d = {.bits = {0x00003C28, 0x00000000, 0x00000000, 0x00020000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test13) {
  s21_decimal d_val = {.bits = {0, 0, 0, 0x80000000}},
              d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test14) {
  s21_decimal d_val = {.bits = {0x000007CF, 0x00000000, 0x00000000,
                                0x00000000}},
              d = {.bits = {0x00004E20, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test15) {
  s21_decimal d_val = {.bits = {0x0000000F, 0x00000014, 0x00000000,
                                0x800A0000}},
              d = {.bits = {0x0000000D, 0x00000014, 0x00000000, 0x800A0000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test16) {
  s21_decimal d_val = {.bits = {0x0000000F, 0x00000014, 0x0000072E,
                                0x800A0000}},
              d = {.bits = {0x0000000F, 0x00000013, 0x0000072E, 0x800A0000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test17) {
  s21_decimal d_val = {.bits = {0x0000000F, 0x00000014, 0x0000072E,
                                0x00020000}},
              d = {.bits = {0x0000000F, 0x00000014, 0x0000072F, 0x00020000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test18) {
  s21_decimal d_val = {.bits = {0x99362457, 0x0007AE79, 0x00000000,
                                0x00080000}},
              d = {.bits = {0x99362457, 0x0007AE79, 0x00000000, 0x00080000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test19) {
  s21_decimal d_val = {.bits = {0x99362457, 0x0007AE79, 0x00000000,
                                0x00080000}},
              d = {.bits = {0x99362458, 0x0007AE79, 0x00000000, 0x00080000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test20) {
  s21_decimal d_val = {.bits = {0x99362457, 0x0007AE79, 0x00000000,
                                0x00080000}},
              d = {.bits = {0x99362456, 0x0007AE79, 0x00000000, 0x00080000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test21) {
  s21_decimal d_val = {.bits = {0x00003225, 0x00000000, 0x00000000,
                                0x80020000}},
              d = {.bits = {0x00003225, 0x00000000, 0x00000000, 0x80020000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test22) {
  s21_decimal d_val = {.bits = {0x0001E0F4, 0x00000000, 0x00000000,
                                0x00030000}},
              d = {.bits = {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test23) {
  s21_decimal d_val = {.bits = {0x00003C28, 0x00000000, 0x00000000,
                                0x80020000}},
              d = {.bits = {0x0000009A, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 1);
}
END_TEST

START_TEST(is_equal_test24) {
  s21_decimal d_val = {.bits = {0x000046CC, 0x00000000, 0x00000000,
                                0x00000000}},
              d = {.bits = {0x000042E3, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

START_TEST(is_equal_test25) {
  s21_decimal d_val = {.bits = {0x000046CA, 0x00000000, 0x00000000,
                                0x00030000}},
              d = {.bits = {0x000042E3, 0x00000000, 0x00000000, 0x00030000}};
  ck_assert_int_eq(s21_is_equal(d_val, d), 0);
}
END_TEST

Suite *s21_is_equal_suite(void) {
  Suite *s = suite_create("IS_EQUAL");
  TCase *tc_core = tcase_create("Is_equal");
  tcase_add_test(tc_core, is_equal_test0);
  tcase_add_test(tc_core, is_equal_test1);
  tcase_add_test(tc_core, is_equal_test2);
  tcase_add_test(tc_core, is_equal_test3);
  tcase_add_test(tc_core, is_equal_test4);
  tcase_add_test(tc_core, is_equal_test5);
  tcase_add_test(tc_core, is_equal_test6);
  tcase_add_test(tc_core, is_equal_test7);
  tcase_add_test(tc_core, is_equal_test8);
  tcase_add_test(tc_core, is_equal_test9);
  tcase_add_test(tc_core, is_equal_test10);
  tcase_add_test(tc_core, is_equal_test11);
  tcase_add_test(tc_core, is_equal_test12);
  tcase_add_test(tc_core, is_equal_test13);
  tcase_add_test(tc_core, is_equal_test14);
  tcase_add_test(tc_core, is_equal_test15);
  tcase_add_test(tc_core, is_equal_test16);
  tcase_add_test(tc_core, is_equal_test17);
  tcase_add_test(tc_core, is_equal_test18);
  tcase_add_test(tc_core, is_equal_test19);
  tcase_add_test(tc_core, is_equal_test20);
  tcase_add_test(tc_core, is_equal_test21);
  tcase_add_test(tc_core, is_equal_test22);
  tcase_add_test(tc_core, is_equal_test23);
  tcase_add_test(tc_core, is_equal_test24);
  tcase_add_test(tc_core, is_equal_test25);
  suite_add_tcase(s, tc_core);
  return s;
}