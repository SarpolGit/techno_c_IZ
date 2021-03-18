#include "gtest/gtest.h"

extern "C" {
#include "../functions.h"
#include <stdlib.h>
}

TEST(translate_to_roman, first_test) {
  int len = 0;
  char* test_str = translate_to_roman(129, &len);
  ASSERT_STREQ("CXXIX", test_str);
  ASSERT_EQ(5, len);
  free(test_str);
}

TEST(translate_to_roman, second_test) {
  int len = 0;
  char* test_str = translate_to_roman(7, &len);
  ASSERT_STREQ("VII", test_str);
  ASSERT_EQ(3, len);
  free(test_str);
}

TEST(translate_to_roman, third_test) {
  int len = 0;
  char* test_str = translate_to_roman(4528, &len);
  ASSERT_STREQ("MMMMDXXVIII", test_str);
  ASSERT_EQ(11, len);
  free(test_str);
}

TEST(translate_to_roman, fourth_test) {
  int len = 0;
  char* test_str = translate_to_roman(999, &len);
  ASSERT_STREQ("CMXCIX", test_str);
  ASSERT_EQ(6, len);
  free(test_str);
}

TEST(translate_to_roman, fifth_test) {
  int len = 0;
  char* test_str = translate_to_roman(1001, &len);
  ASSERT_STREQ("MI", test_str);
  ASSERT_EQ(2, len);
  free(test_str);
}

TEST(translate_to_roman, first_big_integer) {
  int len = 0;
  char* test_str = translate_to_roman(10000000, &len);
  ASSERT_STREQ("Invalid input", test_str);
  ASSERT_EQ(0, len);
  free(test_str);
}

TEST(translate_to_roman, second_big_integer) {
  int len = 0;
  char* test_str = translate_to_roman(10001, &len);
  ASSERT_STREQ("Invalid input", test_str);
  ASSERT_EQ(0, len);
  free(test_str);
}

TEST(translate_to_roman, first_negative_int) {
  int len = 0;
  char* test_str = translate_to_roman(-123, &len);
  ASSERT_STREQ("Invalid input", test_str);
  ASSERT_EQ(0, len);
  free(test_str);
}

TEST(translate_to_roman, second_negative_int) {
  int len = 0;
  char* test_str = translate_to_roman(-10000000, &len);
  ASSERT_STREQ("Invalid input", test_str);
  ASSERT_EQ(0, len);
  free(test_str);
}

TEST(exception, some_errors) {
  char error_text[] = "ERROR";
  char* test_str = exception(error_text);
  ASSERT_STREQ("ERROR", test_str);
  free(test_str);

  char error_text2[] = "Value problem";
  char* test_str2 = exception(error_text2);
  ASSERT_STREQ("Value problem", test_str2);
  free(test_str2);
}
