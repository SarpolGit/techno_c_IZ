#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main(void) {
  printf("Write a number:");

  int number_to_change;
  scanf("%d", &number_to_change); /*Если на этом этапе пользователь
                                  вводит не целочисленный тип в
                                  переменную записывается -1 */

  int len = 0;
  char* result = translate_to_roman(number_to_change, &len);
  printf("Result:%s\n", result);
  free(result);
  printf("Length is:%d\n", len);

  return 0;
}