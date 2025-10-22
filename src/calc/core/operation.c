#include "operation.h"
#include "../../types/operators.h"
#include <stdio.h>
#include <stdlib.h>

binary_op_t set_operation(char op) {
  switch (op) {
  case add_operator:
    return add;
  case sub_operator:
    return subtraction;
  case mult_operator:
    return multiplication;
  case div_operator:
    return division;
  default:
    return NULL;
  }
}

int add(int a, int b) { return a + b; }

int subtraction(int a, int b) { return a - b; }

int multiplication(int a, int b) { return a * b; }

int division(int a, int b) {
  if (b != 0) {
    return a / b;
  }

  fprintf(stderr, "%s", "Não é possível realizar divisão por 0\n");
  return -1;
}
