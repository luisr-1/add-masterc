#ifndef NUMBER_H
#define NUMBER_H

#include <stdbool.h>

/*
 * The numbers assigned in the constants macros is the representation from ASCII
 * TABLE
 * @NINE -> the value 57 is the equivalent to char 9
 * @ZERO -> the value 48 is the equivalent to char 0
 */
#define NINE 57
#define ZERO 48

typedef struct Number Num;

struct Number {
  void *numeric; //Numeric gonna be generic. Int or BigInt
};

bool isValidDigit(char digit);
#endif
