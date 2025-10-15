#include "operation.h"
#include "../../types/operators.h"
#include <stdlib.h>

void *set_operation(char op) {
  switch (op) {
  case add_operator:
    return (void *)add;
    break;
  case sub_operator:
    return (void *)subtraction;
    break;
  case mult_operator:
    return (void *)multiplication;
    break;
  case div_operator:
    return (void *)division;
    break;
  default:
    return NULL;
  }
}
