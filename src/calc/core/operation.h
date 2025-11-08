#ifndef OPERATION_H
#define OPERATION_H

typedef int (*binary_op_t)(int, int);

binary_op_t set_operation(char op);

int add(int a, int b);
int multiplication(int a, int b);
int division(int a, int b);
int subtraction(int a, int b);
int fatorial(int a, int b);


#endif
