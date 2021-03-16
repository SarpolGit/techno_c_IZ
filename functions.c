#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* letters[13] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                     "XL", "X",  "IX", "V",  "IV", "I"};
int numbers[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

char* exception(char* exception_type) {  //Вывод Сообщения об ошибке
  size_t exception_type_len = strlen(exception_type) + 1;
  char* error_string = (char*)malloc(sizeof(char) * exception_type_len);
  memcpy(error_string, exception_type, exception_type_len);
  return error_string;
}

char* translate_to_roman(int number_to_change, int* len) {
  if (number_to_change > 10000) return exception("Invalid input");
  if (number_to_change < 0) return exception("Invalid input");

  *len = 0;
  char* result_string = (char*)malloc(sizeof(char));
  if (result_string == NULL) return exception("Insufficient memory available");
  int count;

  for (int i = 0; i < sizeof(letters) / sizeof(char*); i++) {
    if (number_to_change / numbers[i] > 0) {
      if (i % 2 == 0) {  // На чётных позициях находятся однобуквенные
                         // представления чисел
        count = number_to_change / numbers[i];  // Count показывает сколько букв
                                                // надо добавить в рез. строку
        char* tmp_string = result_string;
        result_string = (char*)realloc(result_string, (*len) + count + 1);
        if (result_string == NULL) {
          free(tmp_string);
          *len = 0;
          return exception("Insufficient memory available");
        }

        for (int j = *len; j < *len + count; j++) {
          result_string[j] = letters[i][0];
        }
      } else {  // На нечётных позициях находятся двухбуквенные представления
                // чисел
        count = 2;  // Так как в строку записывается два символа -> count = 2
        char* tmp_string = result_string;
        result_string = (char*)realloc(result_string, (*len) + count + 1);
        if (tmp_string == NULL) {
          free(tmp_string);
          *len = 0;
          return exception("Insufficient memory available");
        }
        result_string[*len] = letters[i][0];
        result_string[*len + 1] = letters[i][1];
      }
      number_to_change = number_to_change % numbers[i];
      *len = *len + count;
    }
  }
  result_string[*len] = '\0';

  return result_string;
}