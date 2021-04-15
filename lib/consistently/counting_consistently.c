#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "counting_consistently.h"

int init_array_line_c(int* array, int array_length){
    if(array == NULL){
        return -1;
    }
    srand(time(NULL));
    for(int i = 0; i < array_length; i++){
        array[i] = rand()%100;
    }
    return 0;
}

struct_sum_c counting_sum_c(int* array, int array_length){
    struct_sum_c result;
    result.even_sum = 0;
    result.odd_sum = 0;
    if (array == NULL){
        return result;
    }
    for(int i = 0; i < array_length; i++){
        if(array[i] % 2 == 0){
            result.even_sum += array[i];
        } else {
            result.odd_sum += array[i];
        }
    }
    return result;
}




