#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct sums_c {
    long int even_sum;
    long int odd_sum;
} struct_sum_c;

int init_array_line_c(int* array, int array_length);
struct_sum_c counting_sum_c(int* array, int array_length);