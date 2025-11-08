#include "calc/core/operation.h"
#include "calc/handlers/handle_operation.h"
#include "view/menu.h"

#include <stdio.h>

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int main(void /*int argc, char **argv*/) {
  show_menu();
  char operator;
  int a, b;

  do {
    printf("Insira um operador: \n");
    scanf("%c", &operator);
    clear_input_buffer();    
    
    if(operator != '!'){
        printf("Insira dois números para realizar a operação: \n");
        scanf("%d%d", &a, &b);
        clear_input_buffer();

        printf("O resultado de %d %c %d = %d\n", a, operator, b,
           get_result(operator, a, b));
    }
    else{

         printf("Insira um numero para realizar a operacao: \n");
         scanf("%d", &a);
         clear_input_buffer();

         printf("O resultado de %d%c = %d\n", a, operator, 
                               get_result(operator, a, 1));
    }
  } while (is_valid_operation(operator));

  return 0;
}
