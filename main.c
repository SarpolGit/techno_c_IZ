#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include "lib/consistently/counting_consistently.h"
#include "lib/parallel/counting_parallel.h"
#include "lib/file/file.h"

char* optarg;

#define  ARRAY_LENGTH  100000000

int main(int argc, char*argv[]) {

    int* array = (int*) malloc(ARRAY_LENGTH * sizeof(int));
    if(array == NULL){
        return -1;
    }

    int opt = 0;
    char* filename = "";
    while ((opt = getopt(argc, argv, "f:m:c")) != -1){
        switch(opt){
            //Параметр создания файла
            case 'm':
                filename = optarg;
                make_file(filename,ARRAY_LENGTH);
                return 0;
                break;
            //Параметр для считывания данных из файла
            case 'f':
                filename = optarg;
                if(file_init_array(filename,array,ARRAY_LENGTH) == -1) return -1;
                break;

            //Параметр для генерации массива (без файла)
            case 'c':
                if (init_array_line_c(array,ARRAY_LENGTH) == -1) return -1;
                break;
        }
    }
    struct timespec start, finish;
    double difference;

    //Последовательная реализация
    struct_sum_c result_c;
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        return -1;
    };
    result_c = counting_sum_c(array,ARRAY_LENGTH);
    if (clock_gettime(CLOCK_REALTIME, &finish) == -1) {
        return -1;
    }
    difference = (finish.tv_sec - start.tv_sec);
    difference += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Odd numbers sum is:%ld\n",result_c.odd_sum);
    printf("Even numbers sum is:%ld\n",result_c.even_sum);
    printf("Runtime is:%f \n", difference);
    
    //Параллельная реализация с использованием потоков
    struct_sum_p result_p;
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        return EXIT_FAILURE;
    };
    result_p = start_parallel(array,ARRAY_LENGTH);
    if (clock_gettime(CLOCK_REALTIME, &finish) == -1) {
        return EXIT_FAILURE;
    }
    difference = (finish.tv_sec - start.tv_sec);
    difference += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Odd numbers sum is:%ld\n",result_p.odd_sum);
    printf("Even numbers sum is:%ld\n",result_p.even_sum);
    printf("Runtime is:%f \n",difference);

    free(array);
    return 0;
}