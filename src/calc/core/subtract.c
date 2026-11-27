#include "subtract.h"
#include "../../types/big_integer.h"
#include "add.h"
#include <stdbool.h>

bigInt differenceBigInt(bigInt a, bigInt b) {
  if (!a || !b || !a->vector || !b->vector)
    return NULL;

  bigInt result = initEmpty((unsigned int)(*a->size));
  if (!result)
    return NULL;

  int borrow = 0;
  for (size_t i = 0; i < *a->size; i++) {
    int diff = (int)a->vector->vector[i] - borrow;
    if (i < *b->size) {
      diff -= (int)b->vector->vector[i];
    }

    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result->vector->vector[i] = (unsigned int)diff;
  }

  *result->size = *a->size;
  result->signal = 1;
  removeLeadingZerosBigInt(result);

  return result;
}

bigInt subtractBigInt(bigInt a, bigInt b) {
  if (!a || !b)
    return NULL;

  if (a->signal != b->signal) {
    bigInt abs_a = copyBigInt(a);
    bigInt abs_b = copyBigInt(b);
    if (!abs_a || !abs_b) {
      if (abs_a)
        abs_a->destroy(abs_a);
      if (abs_b)
        abs_b->destroy(abs_b);
      return NULL;
    }

    abs_a->signal = 1;
    abs_b->signal = 1;

    bigInt res = addBigInt(abs_a, abs_b);
    abs_a->destroy(abs_a);
    abs_b->destroy(abs_b);

    if (res) {
      res->signal = a->signal;
      removeLeadingZerosBigInt(res);
    }
    return res;
  }

  int cmp = compareAbs(a, b);
  if (cmp == 0)
    return intToBigInt(0);

  bigInt res = (cmp > 0) ? differenceBigInt(a, b) : differenceBigInt(b, a);
  if (res) {
    res->signal = (cmp > 0) ? a->signal : -a->signal;
    removeLeadingZerosBigInt(res);
  }

  return res;
}
