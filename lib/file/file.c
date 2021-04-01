#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include "file.h"

void make_file(char* filename, int amount){
    FILE* file = fopen(filename,"w");
     srand(time(NULL));
        for(int i = 0; i < amount; i++) {
            int r = rand() % 100;
            fprintf(file,"%d ",r);
        }
        fclose(file);
}

int file_init_array(char* filename, int* array, int array_length){
    if(array == NULL){
        return -1;
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    for (int i = 0; i < array_length; i++) {
        int number;
        if (fscanf(file, "%d", &number) == 1) {
            array[i] = number;
        } else {
            fclose(file);
            return -1;
        }
    }
    fclose(file);
    return 0;
}