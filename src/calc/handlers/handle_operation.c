#include <stdio.h>
#include <stdbool.h>
enum operators {
    add_operator = '+',
    sub_operator = '-',
    mult_operator = '*',
    div_operator = '/',
    mod_operator = '%',
    fat_operator = '!'
};

bool is_valid_operation(const char operation) {
  return operation == add_operator || operation == sub_operator ||
         operation == mult_operator || operation == div_operator ||
         operation == mod_operator || operation == fat_operator;
}

int get_result(const char op, int a, int b) {
    if(is_valid_operation(op)) {
        binary_op_t operation;
        operation = set_operation(op);
        return operation(a, b);
    }

    fprintf(stderr, "%s", "Operacao nao suportada: ");
    printf("%c", op);
    return -1;
}
