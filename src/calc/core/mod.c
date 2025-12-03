#include "mod.h"
#include "mult.h"
#include "subtract.h"
#include <stdlib.h>

bigInt modBigInt(bigInt a, bigInt b) {
    if (!a || !b)
        return NULL;

    bigDivResult divres = divisionBigInt(a, b);
    if (!divres)
        return NULL;

    bigInt temp = multBigInt(b, divres->quotient);
    if (!temp) {
        divres->quotient->destroy(divres->quotient);
        divres->remainder->destroy(divres->remainder);
        free(divres);
        return NULL;
    }

    bigInt result = subtractBigInt(a, temp);
    if(!result)
        return NULL; 
    
    result->destroy(temp);
    return result;
}
