#include "s21_tests.h"

START_TEST(float_to_decimal_test1) {
  float f = 0.123f;
  s21_decimal s21_d, d = {.bits = {123, 0, 0, 0}};
  d.bits[3] |= (3 << 16);
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test2) {
  float f = 123456789.0f;
  s21_decimal s21_d, d = {.bits = {123456800, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test3) {
  float f = 123456719.0f;
  s21_decimal s21_d, d = {.bits = {123456700, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test4) {
  float f = 1230000.0f;
  s21_decimal s21_d, d = {.bits = {1230000, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test5) {
  float f = 1234.0f;
  s21_decimal s21_d, d = {.bits = {1234, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test6) {
  float f = 1234.5678f;
  s21_decimal s21_d, d = {.bits = {1234568, 0, 0, 0}};
  d.bits[3] |= (3 << 16);
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test7) {
  float f = 79228162514264337593543950335.0f;
  s21_decimal s21_d, d = {.bits = {0x20000000, 0xB392B21A, 0xFFFFFF77, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test8) {
  float f = 0.000000000000000000000000001f;
  s21_decimal s21_d, d = {.bits = {1, 0, 0, 0}};
  d.bits[3] |= (27 << 16);
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test9) {
  float f = 0.0000000000000000000000000001f;
  s21_decimal s21_d, d = {.bits = {1, 0, 0, 0}};
  d.bits[3] |= (28 << 16);
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test10) {
  float f = 0.00000000000000000000000000001;
  s21_decimal s21_d, d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 1);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test11) {
  float f = 792281625142643375935439503355.00f;
  s21_decimal s21_d, d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 1);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test12) {
  float f = INFINITY;
  s21_decimal s21_d, d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 1);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test13) {
  float f = NAN;
  s21_decimal s21_d, d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 1);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test14) {
  float f = 0.0f;
  s21_decimal s21_d, d = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test15) {
  float f = -0.0000000000000000000000001234f;
  s21_decimal s21_d, d = {.bits = {1234, 0, 0, S21_MINUS}};
  d.bits[3] |= (28 << 16);
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test16) {
  float f = 0.00000000000000000000000012345f;
  s21_decimal s21_d, d = {.bits = {1235, 0, 0, 0}};
  d.bits[3] |= (28 << 16);
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test17) {
  float f = 123456787546435434.0f;
  s21_decimal s21_d, d = {.bits = {0x351B4000, 0x01B69B4E, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test18) {
  float f = -123456787546435434.0f;
  s21_decimal s21_d, d = {.bits = {0x351B4000, 0x01B69B4E, 0, S21_MINUS}};
  ck_assert_int_eq(s21_from_float_to_decimal(f, &s21_d), 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(s21_d.bits[i], d.bits[i]);
  }
}
END_TEST

START_TEST(float_to_decimal_test19) {
  float f = -123456787546435434.0f;
  ck_assert_int_eq(s21_from_float_to_decimal(f, NULL), 1);
}
END_TEST

Suite *s21_float_to_decimal_suite(void) {
  Suite *s = suite_create("FLOAT TO DECIMAL");
  TCase *tc_core = tcase_create("Core float to decimal");
  tcase_add_test(tc_core, float_to_decimal_test1);
  tcase_add_test(tc_core, float_to_decimal_test2);
  tcase_add_test(tc_core, float_to_decimal_test3);
  tcase_add_test(tc_core, float_to_decimal_test4);
  tcase_add_test(tc_core, float_to_decimal_test5);
  tcase_add_test(tc_core, float_to_decimal_test6);
  tcase_add_test(tc_core, float_to_decimal_test7);
  tcase_add_test(tc_core, float_to_decimal_test8);
  tcase_add_test(tc_core, float_to_decimal_test9);
  tcase_add_test(tc_core, float_to_decimal_test10);
  tcase_add_test(tc_core, float_to_decimal_test11);
  tcase_add_test(tc_core, float_to_decimal_test12);
  tcase_add_test(tc_core, float_to_decimal_test13);
  tcase_add_test(tc_core, float_to_decimal_test14);
  tcase_add_test(tc_core, float_to_decimal_test15);
  tcase_add_test(tc_core, float_to_decimal_test16);
  tcase_add_test(tc_core, float_to_decimal_test17);
  tcase_add_test(tc_core, float_to_decimal_test18);
  tcase_add_test(tc_core, float_to_decimal_test19);
  suite_add_tcase(s, tc_core);
  return s;
}