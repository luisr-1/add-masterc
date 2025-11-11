#ifndef DIGIT
#define DIGIT

#include <ctype.h>
#include <stdbool.h>

static inline int charToInt(char c) { return isdigit(c) ? c - '0' : -1; }
static inline char intToChar(int i) { return (char)i + '0'; }

typedef struct Digit *digit;
struct Digit {
  digit nxt;
  digit prv;
  char digit_value;
  char carry;
};

digit initDigit(char d);

#endif