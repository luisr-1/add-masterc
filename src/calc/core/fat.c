#include "mult.h"
#include "add.h"
#include "../../types/digit.h"
#include "fat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bigInt fatorialBigInt(bigInt a) {
    bigInt aux = initNumber("1");
    bigInt um = initNumber("1");
    bigInt contador = initNumber("1");

    while(strcmp(a->to_decimal_representation(a), contador->to_decimal_representation(contador)) != 0) {
        aux = multBigInt(aux, contador);
        contador = addBigInt(contador, um);
    }
    aux = multBigInt(aux, contador);
    
    return aux;
}

