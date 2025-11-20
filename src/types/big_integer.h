#ifndef BIG_INTEGER
#define BIG_INTEGER

#include "array.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct BigInteger *bigInt;

typedef bigInt (*Init)(const char *num);
typedef void (*DestroyBigInt)(bigInt self);
typedef char *(*DecimalRepresentation)(bigInt self);

struct BigInteger {
  array vector;
  size_t *size;
  short signal;

  Init init;
  DestroyBigInt destroy;
  DecimalRepresentation to_decimal_representation;
};

bigInt initNumber(const char *num);
char *sanitizeNumber(const char *number);
char *toDecimalRepresentation(bigInt n);
void destroyBigInt(bigInt b);
#endif