#include "../../types/big_integer.h"
#include "add.h"
#include "subtract.h"

bigInt differenceBigInt(bigInt a, bigInt b) {
  if (!a || !b || !a->vector || !b->vector)
    return NULL;

  bigInt result = initEmpty(*a->size);
  if (!result)
    return NULL;

  int borrow = 0;
  for (size_t i = 0; i < *a->size; i++) {
    int diff = a->vector->vector[i] - borrow;
    if (i < *b->size) {
      diff -= b->vector->vector[i];
    }

    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result->vector->vector[i] = diff;
  }

  result->signal = 1;
  
  return result;
}

bigInt subtractBigInt(bigInt a, bigInt b) {
  if (!a || !b)
    return NULL;

  if (a->signal == b->signal) {
    bigInt res = differenceBigInt(a, b);

    if (a->signal == -1 && res) {
      res->signal *= -1;
    }
    return res;
  } else {
    bigInt res = addBigInt(a, b);
    res->signal = a->signal;
    return res;
  }
}
