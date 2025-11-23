#ifndef MULT_H
#define MULT_H
 
#include "../../types/big_integer.h"
 
bigInt multBigInt(bigInt a, bigInt b);
bigInt karatsuba_bigint(bigInt a, bigInt b);  // Mudou para size_t
char* bigint_to_string_reversed(bigInt n);
bigInt string_to_bigint(const char* str);
bigInt combine_bigint(bigInt a, bigInt b);
bigInt difference_bigint(bigInt a, bigInt b);
bigInt shift_left_bigint(bigInt num, int positions);
void remove_leading_zeros_bigint(bigInt n);
 
#endif
