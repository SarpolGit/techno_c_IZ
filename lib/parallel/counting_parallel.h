#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct sums_p {
    long int even_sum;
    long int odd_sum;
} struct_sum_p;

struct_sum_p start_parallel(int* array, int array_length);