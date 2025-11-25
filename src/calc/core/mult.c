#include "subtract.h"
#include "mult.h"
#include "../../types/big_integer.h"
#include "add.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bigInt schoolMultiplyBigInt(bigInt a, bigInt b) {
  if (!a || !b || !a->vector || !b->vector)
    return NULL;

  size_t result_size = *a->size + *b->size;
  bigInt result = initEmpty(result_size);
  if (!result)
    return NULL;

  for (size_t i = 0; i < result_size; i++)
    result->vector->vector[i] = 0;

  for (size_t i = 0; i < *a->size; i++) {
    int carry = 0;
    for (size_t j = 0; j < *b->size; j++) {
      size_t pos = i + j;
      int product = a->vector->vector[i] * b->vector->vector[j] +
                    result->vector->vector[pos] + carry;
      result->vector->vector[pos] = product % 10;
      carry = product / 10;
    }

    size_t carry_pos = i + *b->size;
    while (carry > 0) {
      int total = result->vector->vector[carry_pos] + carry;
      result->vector->vector[carry_pos] = total % 10;
      carry = total / 10;
      carry_pos++;
    }
  }

  result->signal = (a->signal == b->signal) ? 1 : -1;
  return result;
}

bigInt getHighPart(bigInt num, size_t split) {
  if (!num || !num->vector || split >= *num->size)
    return initNumber("0");

  size_t high_size = *num->size - split;
  bigInt result = initEmpty(high_size);
  if (!result)
    return NULL;

  for (size_t i = 0; i < high_size; i++) {
    result->vector->vector[i] = num->vector->vector[i + split];
  }

  result->signal = 1;
  return result;
}

bigInt getLowPart(bigInt num, size_t split) {
  if (!num || !num->vector)
    return initNumber("0");

  size_t low_size = (*num->size < split) ? *num->size : split;
  bigInt result = initEmpty(low_size);
  if (!result)
    return NULL;

  for (size_t i = 0; i < low_size; i++) {
    result->vector->vector[i] = num->vector->vector[i];
  }

  result->signal = 1;

  return result;
}

bigInt karatsubaBigInt(bigInt a, bigInt b) {
  if (!a || !b || !a->vector || !b->vector)
    return NULL;

  if (*a->size <= 4 || *b->size <= 4)
    return schoolMultiplyBigInt(a, b);

  size_t m = (*a->size < *b->size ? *a->size : *b->size) / 2;
  if (m == 0)
    m = 1;

  bigInt a_high = getHighPart(a, m);
  bigInt a_low = getLowPart(a, m);
  bigInt b_high = getHighPart(b, m);
  bigInt b_low = getLowPart(b, m);

  if (!a_high || !a_low || !b_high || !b_low) {
    if (a_high)
      a_high->destroy(a_high);
    if (a_low)
      a_low->destroy(a_low);
    if (b_high)
      b_high->destroy(b_high);
    if (b_low)
      b_low->destroy(b_low);
    return schoolMultiplyBigInt(a, b);
  }

  bigInt z0 = karatsubaBigInt(a_low, b_low);
  bigInt z1 = karatsubaBigInt(a_high, b_high);

  bigInt a_sum = addBigInt(a_low, a_high);
  bigInt b_sum = addBigInt(b_low, b_high);
  bigInt z2 = karatsubaBigInt(a_sum, b_sum);

  if (!z0 || !z1 || !z2) {
    if (z0)
      z0->destroy(z0);
    if (z1)
      z1->destroy(z1);
    if (z2)
      z2->destroy(z2);
    a_high->destroy(a_high);
    a_low->destroy(a_low);
    b_high->destroy(b_high);
    b_low->destroy(b_low);
    a_sum->destroy(a_sum);
    b_sum->destroy(b_sum);
    return schoolMultiplyBigInt(a, b);
  }

  bigInt temp = subtractBigInt(z2, z1);
  bigInt middle_term = subtractBigInt(temp, z0);

  bigInt part1 = shiftLeftBigInt(z1, 2 * m);      // z1 * 10^(2m)
  bigInt part2 = shiftLeftBigInt(middle_term, m); // middle * 10^m

  bigInt sum1 = addBigInt(part1, part2);
  bigInt result = addBigInt(sum1, z0);

  if (result)
    result->signal = (a->signal == b->signal) ? 1 : -1;

  a_high->destroy(a_high);
  a_low->destroy(a_low);
  b_high->destroy(b_high);
  b_low->destroy(b_low);
  a_sum->destroy(a_sum);
  b_sum->destroy(b_sum);
  z0->destroy(z0);
  z1->destroy(z1);
  z2->destroy(z2);
  temp->destroy(temp);
  middle_term->destroy(middle_term);
  part1->destroy(part1);
  part2->destroy(part2);
  sum1->destroy(sum1);

  return result;
}

bigInt multBigInt(bigInt a, bigInt b) {
  if (!a || !b)
    return NULL;

  if ((*a->size == 1 && a->vector->vector[0] == 0) ||
      (*b->size == 1 && b->vector->vector[0] == 0))
    return intToBigInt(0);

  if (*a->size <= 10 || *b->size <= 10)
    return schoolMultiplyBigInt(a, b);

  return karatsubaBigInt(a, b);
}
