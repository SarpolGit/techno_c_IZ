#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include "file.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

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

//Попробовал сделать mmap (Не работает)
int file_init_array_mmap(char* filename, int* array, int array_length){
    if(array == NULL){
        return -1;
    }
    int file = open(filename, O_RDONLY);
    if (file < 0) {
        return -1;
    }
    struct stat size;
    stat(filename, &size);
    char *file_mmap = mmap(NULL, size.st_size, PROT_READ, MAP_SHARED, file, 0);
    if (file_mmap == MAP_FAILED) {
        return -1;
    }
    int number = 0;
    for(int i = 0;i < array_length; i++){
        number = sscanf(file_mmap,"%d",&number);
        array[i] = number;
        if(i % 1000000 == 0){
            printf("i is:%d", i);
        }
        file_mmap = strchr(file_mmap,' ');
    }
    munmap(file_mmap,size.st_size);
    return 0;
}