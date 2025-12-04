#include "mod.h"
#include "division.h"
#include "mult.h"
#include "subtract.h"
#include <stdio.h>
#include <stdlib.h>

bigInt modBigInt(bigInt a, bigInt b) {
    if (!a || !b) {
        return NULL;
    }

    if (*b->size == 1 && b->vector->vector[0] == 0) {
        printf("Erro: módulo por zero.\n");
        return NULL;
    }

    if (compareAbs(a, b) < 0) {
        return copyBigInt(a);
    }

    bigDivResult div = divisionBigInt(a, b);
    if (!div) {
        return NULL;
    }

    bigInt prod = multBigInt(div->quotient, b);
    if (!prod) {
        div->quotient->destroy(div->quotient);
        div->remainder->destroy(div->remainder);
        free(div);
        return NULL;
    }

    bigInt result = subtractBigInt(a, prod);

    prod->destroy(prod);
    div->quotient->destroy(div->quotient);
    div->remainder->destroy(div->remainder);
    free(div);

    if (!result)
        return NULL;

    result->signal = a->signal;

    removeLeadingZerosBigInt(result);

    return result;
}
