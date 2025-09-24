#ifndef NUMBER_H
#define NUMBER_H

#include <stdbool.h>

typedef struct Number Num;

struct Number {
    char* digits;
    bool has_signal;
};

#endif
