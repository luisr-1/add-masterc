#include "handle_operation.h"
#include "../../types/operators.h"

bool is_valid_operation(const char operation) {
  return operation == add_operator || operation == sub_operator ||
         operation == mult_operator || operation == div_operator ||
         operation == mod_operator;
}
