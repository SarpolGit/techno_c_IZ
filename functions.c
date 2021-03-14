#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* letters[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
int numbers[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};

int is_positive(int number) {                                   //Проверка ввода на положительное число
        if (number > 0)       
            return number;

    return -1;
}

char* NULL_exception() {                                        //Вывод Сообщения об ошибке
    char error_text[] = "Exception";
    char* error_string = (char*) malloc(sizeof(char)*10);
    memcpy(error_string, error_text, sizeof(char)*10);    
    return error_string;
}

char* translate_to_roman(int number_to_change, int* len){
    *len = 0;

    number_to_change = is_positive(number_to_change);           // Обработка некорректного ввода
    if(number_to_change == -1){                                 
        char error_text[] = "Invalid input";
        char* error_string = (char*) malloc(sizeof(char)*14);   // Если возвращать сразу char[]
        memcpy(error_string, error_text, sizeof(char)*14);      //возникает ошибка несоответствия типов
        return error_string;
    } 

    char* result_string = (char*) malloc(sizeof(char));
    int count;

    for(int i = 0; i < sizeof(letters) / sizeof(char*); i++){
        if(number_to_change / numbers[i] > 0){
            if(i % 2 ==0){                                  // На чётных позициях находятся однобуквенные представления чисел
            count = number_to_change / numbers[i];          // Count показывает сколько букв надо добавить в рез. строку
            char* tmp_string = (char*) realloc(result_string,(*len) + count + 1);
            if (tmp_string == NULL) return NULL_exception();
            result_string = tmp_string;

                for(int j = *len; j < *len+count; j++){
                    result_string[j] = letters[i][0];
                }
            } else {                                        // На нечётных позициях находятся двухбуквенные представления чисел
                count = 2;                                  // Так как в строку записывается два символа -> count = 2
                char* tmp_string = (char*)realloc(result_string,(*len) + count + 1);
                if (tmp_string == NULL) return NULL_exception();
                result_string = tmp_string;
                result_string[*len] = letters[i][0];
                result_string[*len+1] = letters[i][1];
            }
                number_to_change = number_to_change % numbers[i];
                *len = *len +count;
        }

    } 
    result_string[*len]='\0';

    return result_string;
}
