
#include <stdio.h>
#include <stdlib.h>

typedef int (*binary_op_t)(int, int);

binary_op_t set_operation(char op);

int add(int a, int b);
int multiplication(int a, int b);
int division(int a, int b);
int subtraction(int a, int b);
unsigned long long fatorial(unsigned long long a);

enum operators {
    add_operator = '+',
    sub_operator = '-',
    mult_operator = '*',
    div_operator = '/',
    mod_operator = '%',
    fat_operator = '!'
};

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
  case fat_operator:
    return fatorial;
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

  fprintf(stderr, "%s", "Nao é possivel realizar divisao por 0\n");
  return -1;
}

unsigned long long fatorial(unsigned long long a) {

  unsigned long long result = 1;
  for(int i = 1; i <= a; i++){
    result = result*i;

  }


  return result;

}
