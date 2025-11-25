#include "handle_operation.h"
#include "../../types/operators.h"
#include "../core/add.h"
#include "../core/division.h"
#include "../core/mult.h"
#include "../core/subtract.h"
#include "stdlib.h"

bool isValidOperation(const char operation) {
  return operation == add_operator || operation == sub_operator ||
         operation == mult_operator || operation == div_operator ||
         operation == mod_operator || operation == fat_operator;
}

bigInt getResult(const char op, bigInt a, bigInt b) {
  if (!isValidOperation(op))
    return NULL;
  switch (op) {
  case add_operator:
    return addBigInt(a, b);
  case sub_operator:
    return subtractBigInt(a, b);
  case mult_operator:
    return multBigInt(a, b);
  case div_operator: {
    bigDivResult res = divisionBigInt(a, b);
    if (!res)
      return NULL;
    bigInt quotient = res->quotient;

    if (res->remainder)
      res->remainder->destroy(res->remainder);

    free(res);

    return quotient;
  }
  case mod_operator: {
    bigDivResult res = divisionBigInt(a, b);
    if (!res)
      return NULL;

    bigInt remainder = res->remainder;

    if (res->quotient) {
      res->quotient->destroy(res->quotient);
    }

    free(res);

    return remainder;
  }
  default:
    return NULL;
  }
}
