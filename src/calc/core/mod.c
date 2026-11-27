#include "mod.h"
#include "division.h"
#include <stdio.h>
#include <stdlib.h>

bigInt modBigInt(bigInt a, bigInt b) {
  if (!a || !b || !a->vector || !b->vector)
    return NULL;

  if (*b->size == 1 && b->vector->vector[0] == 0)
    return NULL;

  if (compareAbs(a, b) < 0) {
    bigInt copy = copyBigInt(a);
    if (copy)
      removeLeadingZerosBigInt(copy);
    return copy;
  }

  bigDivResult div = divisionBigInt(a, b);
  if (!div)
    return NULL;

  bigInt remainder = div->remainder;
  if (div->quotient)
    div->quotient->destroy(div->quotient);
  free(div);

  if (remainder)
    removeLeadingZerosBigInt(remainder);

  return remainder;
}
