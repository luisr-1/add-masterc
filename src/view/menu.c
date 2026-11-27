#include "menu.h"
#include <stdio.h>

void show_menu(void) {
  printf("Selecione uma opção de operação a ser realizada com os operandos\n"
         "+ :=> Soma\n"
         "- :=> Subtração\n"
         "* :=> Multiplicação\n"
         "/ :=> Divisão Inteira\n"
         "%% :=> Módulo\n"
         "! :=> Fatorial\n"
         "q :=> Sair\n"
         "================================================\n");
}
