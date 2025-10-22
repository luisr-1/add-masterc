#include "handle_operation.h"
#include "../../types/operators.h"
#include "../core/operation.h"
#include <stdio.h>

bool is_valid_operation(const char operation) {
  return operation == add_operator || operation == sub_operator ||
         operation == mult_operator || operation == div_operator ||
         operation == mod_operator;
}

int get_result(const char op, int a, int b) {
    if(is_valid_operation(op)) {
        binary_op_t operation;
        operation = set_operation(op);
        return operation(a, b);
    }

    fprintf(stderr, "%s", "Operação não suportada: ");
    printf("%c", op);
    return -1;
}
