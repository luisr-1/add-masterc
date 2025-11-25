#ifndef HANDLE_OPERATION_H
#define HANDLE_OPERATION_H
#include <stdbool.h>
#include "../../types/big_integer.h"

bool isValidOperation(const char op);
bigInt getResult(const char op, bigInt a, bigInt b);
#endif
