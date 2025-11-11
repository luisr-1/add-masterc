#include "big_integer.h"
#include "digit.h"
#include <stdlib.h>
#include <string.h>

bigInt initNumber(const char *num) {
  if (num == NULL)
    return NULL;

  char *num_sanitized = sanitizeNumber(num);
  if (num_sanitized == NULL)
    return NULL;

  bigInt n = (bigInt)malloc(sizeof(struct BigInteger));
  if (n == NULL)
    return NULL;

  n->has_signal = (num_sanitized[0] == '-');
  n->first_digit = NULL;
  n->last_digit = NULL;

  size_t i = 0;
  if (n->has_signal)
    i++;

  for (; num_sanitized[i] != '\0'; i++) {
    digit new_digit = initDigit(num_sanitized[i]);
    if (new_digit == NULL) {
      free(num_sanitized);
      // n->destroy(&self);
      return NULL;
    }

    if (n->first_digit == NULL) {
      n->first_digit = new_digit;
      n->last_digit = new_digit;
    } else {
      new_digit->prv = n->last_digit;
      n->last_digit->nxt = new_digit;
      n->last_digit = new_digit;
    }
  }

  free(num_sanitized);
  return n;
}

char *sanitizeNumber(const char *number) {
  if (number == NULL)
    return NULL;

  size_t i = 0;
  char signal = 0;

  while (number[i] == '-') {
    signal = '-';
    i++;
  }

  while (number[i] == '0')
    i++;

  const char *body_start = &number[i];

  if (*body_start == '\0') {
    char *zero_str = malloc(2);
    if (zero_str == NULL)
      return NULL;
    strcpy(zero_str, "0");
    return zero_str;
  }

  int body_len = strlen(body_start);
  int has_signal = (signal == '-');

  char *sanitized = malloc(body_len + has_signal + 1);
  if (sanitized == NULL)
    return NULL;

  int write_pos = 0;
  if (has_signal)
    sanitized[write_pos++] = '-';

  strcpy(&sanitized[write_pos], body_start);

  return sanitized;
}