#include "gtest/gtest.h"

extern "C" {
    #include "../lib/consistently/counting_consistently.h"
    #include "../lib/parallel/counting_parallel.h"
    #include "../lib/file/file.h"
    #include "stdlib.h"
}

TEST(counting_sum_c, counting_correctly_c){
    struct_sum_c sums;
    sums.even_sum = 0;
    sums.odd_sum = 0;
    int array_length = 100;
    int* array = (int*)malloc(array_length*sizeof(int));
    for(int i = 0; i < array_length; i++){
       (i % 2 == 0) ? array[i] = 2 : array[i] = 1;
    }
    sums = counting_sum_c(array,array_length);
    EXPECT_EQ(sums.even_sum,100);
    EXPECT_EQ(sums.odd_sum,50);
    free(array);
}
TEST(counting_sum_c, NULL_ARRAY){
    struct_sum_c sums;
    sums.even_sum = 0;
    sums.odd_sum = 0;
    sums = counting_sum_c(NULL,10);
    EXPECT_EQ(sums.even_sum,0);
    EXPECT_EQ(sums.odd_sum,0);
}
TEST(start_parallel, counting_correctly_p){
    struct_sum_p sums;
    sums.even_sum = 0;
    sums.odd_sum = 0;
    int array_length = 100;
    int* array = (int*)malloc(array_length*sizeof(int));
    for(int i = 0; i < array_length; i++){
       (i % 2 == 0) ? array[i] = 2 : array[i] = 1;
    }
    sums = start_parallel(array,array_length);
    EXPECT_EQ(sums.even_sum,100);
    EXPECT_EQ(sums.odd_sum,50);
    free(array);
    
}
TEST(start_parallel, NULL_ARRAY){
    struct_sum_p sums;
    sums.even_sum = 0;
    sums.odd_sum = 0;
    sums = start_parallel(NULL,10);
    EXPECT_EQ(sums.even_sum,0);
    EXPECT_EQ(sums.odd_sum,0);
}
TEST(init_array_line_c, NULL_ARRAY){
    int error_flag = init_array_line_c(NULL,10);
    EXPECT_EQ(error_flag,-1);
}
TEST(init_array_line_c, correct_random){
    int array_length = 10;
    int* array = (int*) malloc(array_length * sizeof(int));
    int fl = init_array_line_c(array,array_length);
    if (fl == -1) FAIL();
    for(int i = 0; i<array_length; i++){
        if (array[i]< 0 && array[i] > 99)
            FAIL();
    }
    free(array);
}
TEST(file_init_array,no_file){
    char filename[] = "1.txt";
    int array_length = 10;
    int* array = (int*) malloc(array_length * sizeof(int));
    int error = file_init_array(filename,array,array_length);
    EXPECT_EQ(-1,error);
    free(array);
}
TEST(start_parallel,is_equal){
    struct_sum_p sums_p;
    sums_p.even_sum = 0;
    sums_p.odd_sum = 0;

    struct_sum_c sums_c;
    sums_c.even_sum = 0;
    sums_c.odd_sum = 0;

    int array_length = 100;
    int* array = (int*)malloc(array_length*sizeof(int));
    for(int i = 0; i < array_length; i++){
       (i % 2 == 0) ? array[i] = 2 : array[i] = 1;
    }
    sums_p = start_parallel(array,array_length);
    sums_c = counting_sum_c(array,array_length);
    EXPECT_EQ(sums_p.even_sum,sums_c.even_sum);
    EXPECT_EQ(sums_p.odd_sum,sums_c.odd_sum);
    free(array);
}