#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "counting_parallel.h"

pthread_mutex_t mutex;

typedef struct arg {
    int* array;
    int array_length;
    int thread_number;
    int threads_amount;
    struct_sum_p* presult;
} struct_p;

void* counting_sum_p(void* arg){
    struct_sum_p local_sum;
    local_sum.even_sum = 0;
    local_sum.odd_sum = 0;
    struct_p* args = (struct_p*) arg;
    for(int i = (*args).thread_number; i < (*args).array_length; i += (*args).threads_amount){
        if((*args).array[i] % 2 == 0){
            local_sum.even_sum += (*args).array[i];
        } else {
            local_sum.odd_sum += (*args).array[i];
        }
    }

    pthread_mutex_lock(&mutex);
    (*args).presult->even_sum += local_sum.even_sum;
    (*args).presult->odd_sum += local_sum.odd_sum;
    pthread_mutex_unlock(&mutex);

    return arg;
}

struct_sum_p start_parallel(int* array, int array_length){
    struct_sum_p result;
    result.odd_sum = 0;
    result.even_sum = 0;
    if(array == NULL){
        return result;
    }
    int threads_amount = sysconf(_SC_NPROCESSORS_ONLN);
    struct_p args[threads_amount];
    pthread_t threadIds[threads_amount];

    //Инициализация структур
    for(int i = 0; i < threads_amount; i++){
        args[i].array = array;
        args[i].array_length = array_length;
        args[i].thread_number = i;
        args[i].threads_amount =threads_amount;
        args[i].presult = &result;
    }
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < threads_amount; i++){   
        int errflag = pthread_create(&threadIds[i], NULL, counting_sum_p, (void *)&args[i]);
        if (errflag != 0){
        }
    }

    for (size_t i = 0; i < threads_amount; i++) {
        pthread_join(threadIds[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return result;
}