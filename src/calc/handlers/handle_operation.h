#ifndef HANDLE_OPERATION_H
#define HANDLE_OPERATION_H
#include <stdbool.h>

bool is_valid_operation(const char op);
int get_result(const char op, int a, int b);
#endif
