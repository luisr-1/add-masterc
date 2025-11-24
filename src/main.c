#include "calc/core/mult.h"
#include "calc/core/fat.h"
#include <stdlib.h>
#include <stdio.h>
 
int main() {
    // Teste com números grandes
    bigInt num1 = initNumber("9");
    bigInt num2 = initNumber("9888888888");
 
    bigInt result = multBigInt(num1, num2);
    printf("cheguei");
    bigInt fatorial = fatorialBigInt(num1);
    printf("passei\n\n");
    char* result_str = result->to_decimal_representation(result);
    printf("Resultado mult: %s\n\n", result_str);
    printf("Resultado !: %s\n\n", fatorial->to_decimal_representation(fatorial));
            
    fatorial->destroy(fatorial);
    free(result_str);
    result->destroy(result);
 
    num1->destroy(num1);
    num2->destroy(num2);
    
 
    return 0;
}
