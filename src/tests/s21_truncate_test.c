#include "s21_tests.h"

START_TEST(truncate_test0) {
  s21_decimal s21_d, d_val = {.bits = {1, 2, 3, 40 << 16}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 1);
}
END_TEST

START_TEST(truncate_test1) {
  s21_decimal d_val = {.bits = {S21_MINUS, 0, 0, 0}};
  ck_assert_int_eq(s21_truncate(d_val, NULL), 1);
}
END_TEST

START_TEST(truncate_test2) {
  s21_decimal s21_d, d_val = {.bits = {1, 0, 0, 0}}, d = {.bits = {1, 0, 0, 0}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test3) {
  s21_decimal s21_d, d_val = {.bits = {1, 0, 0, 0x80000000}},
                     d = {.bits = {1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test4) {
  s21_decimal s21_d, d_val = {.bits = {0xCF5C048C, 0x004D2BEF, 0, 0x00070000}},
                     d = {.bits = {0x8178F63A, 0, 0, 0}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test5) {
  s21_decimal s21_d,
      d_val = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
      d = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test6) {
  s21_decimal s21_d, d_val = {.bits = {0, 0, 0, 0x80020000}},
                     d = {.bits = {0, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test7) {
  s21_decimal s21_d, d_val = {.bits = {0x000F4240, 0, 0, 0x00020000}},
                     d = {.bits = {0x00002710, 0, 0, 0}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test8) {
  s21_decimal s21_d,
      d_val = {.bits = {0x00000467, 0x0000007A, 0x00205FF0, 0x80020000}},
      d = {.bits = {0xBD70A3E2, 0x1EB851EC, 0x000052E1, 0x80000000}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test9) {
  s21_decimal s21_d,
      d_val = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}},
      d = {.bits = {0x00000007, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test10) {
  s21_decimal s21_d, d_val = {.bits = {0, 0, 0, 0}}, d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test11) {
  s21_decimal s21_d,
      d_val = {.bits = {0x1FC40A5D, 0xA98FD4BE, 0x00000000, 0x00020000}},
      d = {.bits = {0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test12) {
  s21_decimal s21_d,
      d_val = {.bits = {0x1FC40A5F, 0xA98FD4BE, 0x00000000, 0x00020000}},
      d = {.bits = {0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(truncate_test13) {
  s21_decimal s21_d,
      d_val = {.bits = {0x1FC40A5F, 0xA98FD4BE, 0x00000000, 0x80020000}},
      d = {.bits = {0x24285C43, 0x01B2140C, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_truncate(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

Suite *s21_truncate_suite(void) {
  Suite *s = suite_create("TRUNCATE");
  TCase *tc_core = tcase_create("Truncate");
  tcase_add_test(tc_core, truncate_test0);
  tcase_add_test(tc_core, truncate_test1);
  tcase_add_test(tc_core, truncate_test2);
  tcase_add_test(tc_core, truncate_test3);
  tcase_add_test(tc_core, truncate_test4);
  tcase_add_test(tc_core, truncate_test5);
  tcase_add_test(tc_core, truncate_test6);
  tcase_add_test(tc_core, truncate_test7);
  tcase_add_test(tc_core, truncate_test8);
  tcase_add_test(tc_core, truncate_test9);
  tcase_add_test(tc_core, truncate_test10);
  tcase_add_test(tc_core, truncate_test11);
  tcase_add_test(tc_core, truncate_test12);
  tcase_add_test(tc_core, truncate_test13);
  suite_add_tcase(s, tc_core);
  return s;
}