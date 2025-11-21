#include "add.h"
#include "../../types/big_integer.h"
#include <stdio.h>

bigInt addBigInt(bigInt a, bigInt b) {
  if (!a || !b)
    return NULL;

  size_t max = *a->size > *b->size ? *a->size : *b->size;

  bigInt c = initEmpty(max + 1);
  if (!c)
    return NULL;

  unsigned short carry = 0;

  for (size_t i = 0; i < max; i++) {
    unsigned short da = (i < *a->size) ? a->vector->vector[i] : 0;
    unsigned short db = (i < *b->size) ? b->vector->vector[i] : 0;

    unsigned short sum = da + db + carry;

    carry = sum / 10;
    sum = sum % 10;

    c->vector->add(c->vector, sum);
  }

  if (carry)
    c->vector->add(c->vector, carry);

  return c;
}
