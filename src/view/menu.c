#include "menu.h"
#include <stdio.h>

void show_menu() {
    printf("Selecione uma opção de operação a ser realizada com os operandos\n"
        "+ :=> Soma\n"
        "- :=> Subtação\n"
        "* :=> Multiplicação\n"
        "/ :=> Divisão Inteira\n"
        "%% :=> Módulo\n"
        // TODO: Adicionar operação especial a ser definida
    );
}
