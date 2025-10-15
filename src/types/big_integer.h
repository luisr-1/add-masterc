#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <stdbool.h>

typedef struct BigInt *BigInteger;
typedef char* Digits;

struct BigInt {
    Digits sequence_of_digits;
    bool has_signal;
};

BigInteger initBigInteger(char *digits, bool has_signal);
#endif
