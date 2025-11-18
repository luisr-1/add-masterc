#ifndef BIG_INTEGER
#define BIG_INTEGER

#include "array.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct BigInteger *bigInt;

struct BigInteger {
  array vector; 
  size_t size;
  short signal;
};

bigInt initNumber(const char *num);
char *sanitizeNumber(const char *number);
char *toDecimalRepresentation(bigInt n);
void destroyBigInt(bigInt b);
#endif