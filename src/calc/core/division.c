#include "division.h"
#include "../../types/big_integer.h"
#include "subtract.h"
#include <stdio.h>
#include <stdlib.h>

bigDivResult divisionBigInt(bigInt a, bigInt b) {
  if (!a || !b || !a->vector || !b->vector)
    return NULL;

  if (*b->size == 1 && b->vector->vector[0] == 0)
    return NULL;

  bigDivResult res = (bigDivResult)calloc(1, sizeof(struct BigDivResult));
  if (!res) {
    perror("Problema para realizar alocação do resultado da divisão");
    return NULL;
  }

  if (compareAbs(a, b) < 0) {
    res->quotient = intToBigInt(0);
    res->remainder = copyBigInt(a);
    if (!res->quotient || !res->remainder) {
      if (res->quotient)
        res->quotient->destroy(res->quotient);
      if (res->remainder)
        res->remainder->destroy(res->remainder);
      free(res);
      return NULL;
    }
    removeLeadingZerosBigInt(res->remainder);
    return res;
  }

  bigInt abs_b = copyBigInt(b);
  bigInt quotient = intToBigInt(0);
  bigInt current = intToBigInt(0);
  if (!abs_b || !quotient || !current) {
    if (abs_b)
      abs_b->destroy(abs_b);
    if (quotient)
      quotient->destroy(quotient);
    if (current)
      current->destroy(current);
    free(res);
    return NULL;
  }
  abs_b->signal = 1;

  for (size_t idx = *a->size; idx > 0; idx--) {
    appendDigitInPlace(current, (int)a->vector->vector[idx - 1]);
    removeLeadingZerosBigInt(current);

    int digit = 0;
    while (compareAbs(current, abs_b) >= 0) {
      bigInt next = differenceBigInt(current, abs_b);
      if (!next) {
        abs_b->destroy(abs_b);
        quotient->destroy(quotient);
        current->destroy(current);
        free(res);
        return NULL;
      }
      current->destroy(current);
      current = next;
      digit++;
    }

    appendDigitInPlace(quotient, digit);
  }

  abs_b->destroy(abs_b);

  quotient->signal = (a->signal == b->signal) ? 1 : -1;
  removeLeadingZerosBigInt(quotient);

  current->signal = a->signal;
  removeLeadingZerosBigInt(current);

  res->quotient = quotient;
  res->remainder = current;

  return res;
}
