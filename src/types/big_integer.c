#include "big_integer.h"
#include "array.h"
#include "digit.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bigInt initNumber(const char *num) {
  if (!num) {
    perror("A string passada é nula, o número não será inicializado\n");
    return NULL;
  }

  char *num_sanitized = sanitizeNumber(num);
  if (!num_sanitized) {
    perror("Problema na limpeza da string de representação númerica\n");
    return NULL;
  }

  bigInt n = (bigInt)malloc(sizeof(struct BigInteger));
  if (!n) {
    perror("Ocorreu um problema para alocar espaço para o BigInt\n");
    free(num_sanitized);
    return NULL;
  }

  n->destroy = destroyBigInt;
  n->init = initNumber;
  n->to_decimal_representation = toDecimalRepresentation;
  
  size_t i = 0;

  if (num[0] == '-') {
    n->signal = -1;
    i = 1;
  } else {
    n->signal = 1;
    if (num_sanitized[0] == '+')
      i = 1;
  }

  n->size = (size_t *)malloc(sizeof(size_t));
  *n->size = strlen(num_sanitized) - i;

  n->vector = initArray(*n->size);
  if (!n->vector) {
    perror("Erro ao alocar o vetor dinâmico para o dígitos\n");
    destroyBigInt(n);
    free(num_sanitized);
    return NULL;
  }

  for (; i < strlen(num_sanitized) && num_sanitized[i] != '\n' &&
         num_sanitized[i] != EOF;
       i++) {
    if (!isdigit(num_sanitized[i])) {
      perror("Caractere inválido encontrado na string de inicialização\n");
      n->vector->destroy(n->vector);
      destroyBigInt(n);
      free(num_sanitized);
      return NULL;
    }
    n->vector->add_front(n->vector, charToInt(num_sanitized[i]));
  }

  free(num_sanitized);
  return n;
}

char *sanitizeNumber(const char *number) {
  if (!number)
    return NULL;

  size_t i = 0;
  size_t minus_count = 0;

  while (number[i] == '+' || number[i] == '-') {
    if (number[i] == '-')
      minus_count++;
    i++;
  }

  while (number[i] == '0')
    i++;

  if (number[i] == '\0') {
    char *zero = (char *)malloc(sizeof(char) * 2);
    if (!zero)
      return NULL;
    strcpy(zero, "0");
    return zero;
  }

  char signal = 0;
  if (minus_count % 2 == 1)
    signal = '-';

  const char *body = number + i;
  size_t body_len = strlen(body);

  size_t total_len = body_len + (signal ? 1 : 0) + 1;

  char *sanitized = malloc(total_len);
  if (!sanitized)
    return NULL;

  size_t position = 0;
  if (signal)
    sanitized[position++] = signal;

  strcpy(&sanitized[position], body);

  return sanitized;
}

char *toDecimalRepresentation(bigInt b) {
  if (!b) {
    perror("Número passado é nulo, não tem como ser realizado a conversão\n");
    return NULL;
  }

  int has_signal = (b->signal == -1);

  size_t total_len = *b->size + has_signal + 1;
  char *out = (char *)malloc(sizeof(char) * total_len);
  if (!out) {
    perror("Erro na alocação da string para representação númerica\n");
    return NULL;
  }

  size_t position = 0;

  if (has_signal)
    out[position++] = '-';

  for (size_t i = *b->size; i > 0; i--)
    out[position++] = intToChar(b->vector->vector[i - 1]);

  out[position] = '\0';

  return out;
}

void destroyBigInt(bigInt b) {
  if (!b) {
    perror("Ponteiro passado é nulo, nada a fazer\n");
    return;
  }

  if (!b->vector)
    b->vector->destroy(b->vector);

  free(b);
}