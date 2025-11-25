#ifndef DIVISION_H
#define DIVISION_H

#include "../../types/big_integer.h"

typedef struct BigDivResult *bigDivResult;

struct BigDivResult {
    bigInt quotient;
    bigInt remainder;
}; 

bigDivResult divisionBigInt(bigInt a , bigInt b);

#endif
