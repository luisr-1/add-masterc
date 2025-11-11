#ifndef BIG_INTEGER
#define BIG_INTEGER

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "digit.h"

typedef struct BigInteger *bigInt;

struct BigInteger {
  digit first_digit;
  digit last_digit;
  bool has_signal;
};

bigInt initNumber(const char *num);
bigInt initNumberWithValue(digit digits);
char *sanitizeNumber(const char *number);

#endif