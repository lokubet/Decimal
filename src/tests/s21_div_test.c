#include "s21_tests.h"

START_TEST(div_test1) {
  s21_decimal d1 = {{1, 0, 0, 0}}, d2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0x05555555, 0x14B700CB, 0x0AC544CA, 0x001C0000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test2) {
  s21_decimal d1 = {{1, 0, 0, S21_MINUS}}, d2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0x05555555, 0x14B700CB, 0x0AC544CA, 0x801C0000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test3) {
  s21_decimal d1 = {{1, 0, 0, S21_MINUS}}, d2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 3);
}
END_TEST

START_TEST(div_test4) {
  s21_decimal d1 = {{0, 0, 0, 0}}, d2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test5) {
  s21_decimal d1 = {{3, 0, 0, 0}}, d2 = {{1, 0, 0, S21_MINUS}};
  s21_decimal res = {{3, 0, 0, S21_MINUS}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test6) {
  s21_decimal d1 = {{3, 0, 0, 0}}, d2 = {{3, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test7) {
  s21_decimal d1 = {{20, 0, 0, 0}},
              d2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal res = {{2, 0, 0, 0x001C0000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test8) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}},
              d2 = {{0x00000312, 0, 0, 0x00090000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 1);
}
END_TEST

START_TEST(div_test9) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, S21_MINUS}},
              d2 = {{0x00000312, 0, 0, 0x00090000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 2);
}
END_TEST

START_TEST(div_test10) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, S21_MINUS}},
              d2 = {{0x00000312, 0, 0, 0x80090000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 1);
}
END_TEST

START_TEST(div_test11) {
  s21_decimal d1 = {{115, 0, 0, 0}}, d2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0x0000023F, 0, 0, 0x00010000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test12) {
  s21_decimal d1 = {{115, 0, 0, S21_MINUS}}, d2 = {{2, 0, 0, S21_MINUS}};
  s21_decimal res = {{0x0000023F, 0, 0, 0x00010000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test13) {
  s21_decimal d1 = {{0x540BE3FF, 0x00000002, 0, 0}}, d2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0xC6AEA155, 0, 0, 0}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test14) {
  s21_decimal d1 = {{0x0098967F, 0, 0, 0x80070000}},
              d2 = {{0xD4B49FE1, 0x000000E8, 0, 0x000C0000}};
  s21_decimal res = {{0xF97B0D96, 0x28B45460, 0x204FCBFF, 0x801C0000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test15) {
  s21_decimal d1 = {{10, 0, 0, 0}}, d2 = {{2000, 0, 0, 0}};
  s21_decimal res = {{0x00000005, 0, 0, 0x00030000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test16) {
  s21_decimal d1 = {{10, 0, 0, 0}}, d2 = {{2001, 0, 0, 0}};
  s21_decimal res = {{0x9BD58676, 0x15E87A6F, 0x00042243, 0x001B0000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test17) {
  s21_decimal d1 = {{182, 0, 0, 0}}, d2 = {{101, 0, 0, 0}};
  s21_decimal res = {{0x286562DA, 0x460095F9, 0x05D29026, 0x001B0000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test18) {
  s21_decimal d1 = {{2, 0, 0, 0x00060000}},
              d2 = {{0xB2400000, 0x19E0C9BA, 0x0000021E, 0}};
  s21_decimal res = {{0x00000002, 0, 0, 0x001C0000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test19) {
  s21_decimal d1 = {{0x0001E0F3, 0, 0, 0x00060000}},
              d2 = {{0x0001E0F3, 0, 0, 0}};
  s21_decimal res = {{0x00000001, 0, 0, 0x00060000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(div_test20) {
  s21_decimal d1 = {{0x00000054, 0, 0, 0x00070000}},
              d2 = {{0x00000054, 0, 0, 0x00060000}};
  s21_decimal res = {{1, 0, 0, 0x00010000}};
  ck_assert_int_eq(s21_div(d1, d2, &d1), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(d1.bits[i], res.bits[i]);
  }
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s = suite_create("DIV");
  TCase *tc_core = tcase_create("Core div");
  tcase_add_test(tc_core, div_test1);
  tcase_add_test(tc_core, div_test2);
  tcase_add_test(tc_core, div_test3);
  tcase_add_test(tc_core, div_test4);
  tcase_add_test(tc_core, div_test5);
  tcase_add_test(tc_core, div_test6);
  tcase_add_test(tc_core, div_test7);
  tcase_add_test(tc_core, div_test8);
  tcase_add_test(tc_core, div_test9);
  tcase_add_test(tc_core, div_test10);
  tcase_add_test(tc_core, div_test11);
  tcase_add_test(tc_core, div_test12);
  tcase_add_test(tc_core, div_test13);
  tcase_add_test(tc_core, div_test14);
  tcase_add_test(tc_core, div_test15);
  tcase_add_test(tc_core, div_test16);
  tcase_add_test(tc_core, div_test17);
  tcase_add_test(tc_core, div_test18);
  tcase_add_test(tc_core, div_test19);
  tcase_add_test(tc_core, div_test20);
  suite_add_tcase(s, tc_core);
  return s;
}
