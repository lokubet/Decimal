#include "s21_tests.h"

START_TEST(floor_test0) {
  s21_decimal s21_d, d_val = {.bits = {1, 2, 3, 40 << 16}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 1);
}
END_TEST

START_TEST(floor_test1) {
  s21_decimal d_val = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_floor(d_val, NULL), 1);
}
END_TEST

START_TEST(floor_test2) {
  s21_decimal s21_d,
      d_val = {.bits = {0x00000000, 0x00000000, 0x00000000, 0x00020000}},
      d = {.bits = {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test3) {
  s21_decimal s21_d,
      d_val = {.bits = {0x1FC40A5F, 0xA98FD4BE, 0x00000000, 0x00020000}},
      d = {.bits = {0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test4) {
  s21_decimal s21_d,
      d_val = {.bits = {0x1FC40A5F, 0xA98FD4BE, 0x00000000, 0x80020000}},
      d = {.bits = {0x24285C44, 0x01B2140C, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test5) {
  s21_decimal s21_d,
      d_val = {.bits = {0xC2AC6A00, 0x00000021, 0x00000000, 0x000A0000}},
      d = {.bits = {0x0000000E, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test6) {
  s21_decimal s21_d,
      d_val = {.bits = {0x075BCD15, 0x00000000, 0x00000000, 0x001B0000}},
      d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test7) {
  s21_decimal s21_d,
      d_val = {.bits = {0xFFFFFFFF, 0x00000000, 0x00000000, 0x80060000}},
      d = {.bits = {0x000010C7, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test8) {
  s21_decimal s21_d,
      d_val = {.bits = {0x000F4240, 0x00000000, 0x00000000, 0x80020000}},
      d = {.bits = {0x00002710, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test9) {
  s21_decimal s21_d,
      d_val = {.bits = {0x000F4240, 0x00000000, 0x00000000, 0x00020000}},
      d = {.bits = {0x00002710, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test10) {
  s21_decimal s21_d,
      d_val = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
      d = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test11) {
  s21_decimal s21_d,
      d_val = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
      d = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test12) {
  s21_decimal s21_d,
      d_val = {.bits = {0xFEADBDA2, 0x000001FB, 0x00000000, 0x80060000}},
      d = {.bits = {0x00214ABE, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(floor_test13) {
  s21_decimal s21_d,
      d_val = {.bits = {0xCF5C048C, 0x004D2BEF, 0x00000000, 0x00070000}},
      d = {.bits = {0x8178F63A, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_floor(d_val, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

Suite *s21_floor_suite(void) {
  Suite *s = suite_create("FLOOR");
  TCase *tc_core = tcase_create("Floor");
  tcase_add_test(tc_core, floor_test0);
  tcase_add_test(tc_core, floor_test1);
  tcase_add_test(tc_core, floor_test2);
  tcase_add_test(tc_core, floor_test3);
  tcase_add_test(tc_core, floor_test4);
  tcase_add_test(tc_core, floor_test5);
  tcase_add_test(tc_core, floor_test6);
  tcase_add_test(tc_core, floor_test7);
  tcase_add_test(tc_core, floor_test8);
  tcase_add_test(tc_core, floor_test9);
  tcase_add_test(tc_core, floor_test10);
  tcase_add_test(tc_core, floor_test11);
  tcase_add_test(tc_core, floor_test12);
  tcase_add_test(tc_core, floor_test13);
  suite_add_tcase(s, tc_core);
  return s;
}