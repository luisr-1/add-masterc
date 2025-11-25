#include "division.h"
#include "../../types/big_integer.h"
#include "subtract.h"
#include <stdlib.h>

bigDivResult divisionBigInt(bigInt a, bigInt b) {
  if (*b->size == 1 && b->vector->vector[0] == 0) {
    return NULL;
  }

  bigDivResult res = (bigDivResult)calloc(1, sizeof(struct BigDivResult));
  if (!res) {
    perror("Problema para realizar alocacao do resultado da divisao\n");
    return NULL;
  }

  bigInt quotient = initEmpty(*a->size);
  bigInt remainder = initNumber("0");

  bigInt b_abs = copyBigInt(b);
  b_abs->signal = 1;
  removeLeadingZerosBigInt(b_abs);
  
  for (int i = *a->size - 1; i >= 0; i--) {
    int current_digit = a->vector->vector[i];
    appendDigitInPlace(remainder, current_digit);
    removeLeadingZerosBigInt(remainder);
    
    int count = 0;

    while (compareAbs(remainder, b_abs) >= 0) {
      bigInt diff = subtractBigInt(remainder, b_abs);

      removeLeadingZerosBigInt(diff);
      
      destroyBigInt(remainder);
      remainder = diff;

      count++;
    }

    quotient->vector->vector[i] = count;
  }

  destroyBigInt(b_abs);

  quotient->signal = (a->signal == b->signal) ? 1 : -1;
  remainder->signal = a->signal;

  removeLeadingZerosBigInt(quotient);
  removeLeadingZerosBigInt(remainder);
  res->quotient = quotient;
  res->remainder = remainder;
  return res;
}
