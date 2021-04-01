#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

void make_file(char* filename, int amount);
int file_init_array(char* filename, int* array, int array_length);