#include "calc/core/mult.h"
#include <stdlib.h>
#include <stdio.h>
 
int main() {
    // Teste com números grandes
    bigInt num1 = initNumber("89999999999");
    bigInt num2 = initNumber("98888888888");
 
    if (num1 && num2) {
        bigInt result = multBigInt(num1, num2);
 
        if (result) {
            char* result_str = result->to_decimal_representation(result);
            printf("Resultado: %s\n", result_str);
            free(result_str);
            result->destroy(result);
        }
 
        num1->destroy(num1);
        num2->destroy(num2);
    }
 
    return 0;
}
