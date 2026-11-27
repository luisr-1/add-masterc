#include "add.h"
#include "../../types/big_integer.h"
#include "subtract.h"
#include <stdio.h>

bigInt addBigInt(bigInt a, bigInt b) {
  if (!a || !b)
    return NULL;

  if (a->signal != b->signal) {
    bigInt b_inverted = copyBigInt(b);
    if (!b_inverted)
      return NULL;

    b_inverted->signal = -b->signal;
    bigInt result = subtractBigInt(a, b_inverted);

    b_inverted->destroy(b_inverted);
    return result;
  }

  size_t max = *a->size > *b->size ? *a->size : *b->size;

  bigInt c = initEmpty((unsigned int)(max + 1));
  if (!c)
    return NULL;

  unsigned int carry = 0;

  for (size_t i = 0; i < max; i++) {
    unsigned int da = (i < *a->size) ? a->vector->vector[i] : 0;
    unsigned int db = (i < *b->size) ? b->vector->vector[i] : 0;

    unsigned int sum = da + db + carry;

    carry = sum / 10;
    sum = sum % 10;

    c->vector->add(c->vector, sum);
  }

  if (carry)
    c->vector->add(c->vector, carry);

  c->signal = a->signal;
  removeLeadingZerosBigInt(c);

  return c;
}
