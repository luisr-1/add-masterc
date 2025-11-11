#include "digit.h"
#include <ctype.h>
#include <stdlib.h>

digit initDigit(char algarism) {
  if (isdigit((unsigned char)algarism)) {
    digit d = (digit)malloc(sizeof(struct Digit));
    if (d == NULL)
      return NULL;
    d->digit_value = algarism;
    d->carry = 0;
    d->nxt = NULL;
    d->prv = NULL;
    return d;
  }
  return NULL;
}