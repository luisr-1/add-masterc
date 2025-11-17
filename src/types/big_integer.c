#include "big_integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bigInt initNumber(const char *num) {
  if (num == NULL) {
    perror("A string passada é nula, o número não será inicializado\n");
    return NULL;
  }

  char *num_sanitized = sanitizeNumber(num);
  if (num_sanitized == NULL) {
    perror("Problema na limpeza da string de representação númerica\n");
    return NULL;
  }

  bigInt n = (bigInt)malloc(sizeof(struct BigInteger));
  if (n == NULL) {
    perror("Ocorreu um problema para alocar espaço para o BigInt\n");
    return NULL;
  }

  switch (num_sanitized[0]) {
  case '-':
    n->signal = -1;
    break;
  case '+':
    n->signal = 1;
    break;
  default:
    if (isdigit(num_sanitized[0]))
      n->signal = 0;
    break;
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