#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern "C" {
   #include "functions.h"
}

TEST (translate_to_roman, first_test) {
    int len = 0;
    char* test_str = translate_to_roman(129, &len);
    ASSERT_STREQ("CXXIX", test_str);
    ASSERT_EQ(5, len);
}

TEST (translate_to_roman, negative_int) {
    int len = 0;
    char* test_str = translate_to_roman(-123, &len);
    ASSERT_STREQ("Invalid input", test_str);
    ASSERT_EQ(0, len);
}

TEST (is_positive, second_test){
    int r = is_positive(100);
    ASSERT_EQ(100, r);
}

TEST (is_positive, negative_int){
    int r = is_positive(-233);
    ASSERT_EQ(-1, r);
}

int main(int argc, char** argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}