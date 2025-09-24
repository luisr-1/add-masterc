#include "calc/handlers/handle_operation.h"
#include "view/menu.h"

#include <stdio.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void /*int argc, char **argv*/) {
  show_menu();
  char operator;

  do {
    printf("Insira um operador: \n");
    scanf("%c", &operator);
    clear_input_buffer();
  } while (is_valid_operation(operator));

  return 0;
}
