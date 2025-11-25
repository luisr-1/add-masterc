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

  bigInt n = (bigInt)calloc(1, sizeof(struct BigInteger));
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

  n->size = (size_t *)calloc(1, sizeof(size_t *));
  *n->size = strlen(num_sanitized) - i;

  n->vector = initArray(*n->size);
  if (!n->vector) {
    perror("Erro ao alocar o vetor dinâmico para o dígitos\n");
    destroyBigInt(n);
    free(num_sanitized);
    return NULL;
  }

  size_t max_length = strlen(num_sanitized);
  for (; i < max_length; i++) {
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
    char *zero = (char *)calloc(2, sizeof(char));
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

  char *sanitized = calloc(total_len, sizeof(char));
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
  char *out = (char *)calloc(total_len, sizeof(char));
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

  return sanitizeNumber(out);
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

bigInt initEmpty(const unsigned int size) {
  if (size == 0)
    return NULL;

  bigInt b = (bigInt)calloc(1, sizeof(struct BigInteger));
  if (!b) {
    perror("Erro ao alocar bigInt vazio\n");
    return NULL;
  }

  b->vector = initArray(size);
  if (!b->vector) {
    perror("Erro ao inicializar o array de digitos\n");
    return NULL;
  }

  b->size = (size_t *)calloc(1, sizeof(size_t *));
  if (!b->size) {
    perror("Problema ao alocar o tamanho do BigInteger\n");
    return NULL;
  }

  (*b->size) = size;
  b->signal = 0;

  b->destroy = destroyBigInt;
  b->to_decimal_representation = toDecimalRepresentation;
  b->init = initNumber;
  b->newBigInt = initEmpty;

  return b;
}

bigInt intToBigInt(unsigned int n) {
  char buffer[128];
  sprintf(buffer, "%u", n);
  return initNumber(buffer);
}

bigInt shiftLeftBigInt(bigInt num, int positions) {
  if (!num || !num->vector)
    return NULL;

  if (positions == 0) {
    return initNumber(num->to_decimal_representation(num));
  }

  bigInt result = initEmpty(*num->size + positions);
  if (!result)
    return NULL;

  for (int i = 0; i < positions; i++)
    result->vector->vector[i] = 0;

  for (size_t i = 0; i < *num->size; i++)
    result->vector->vector[i + positions] = num->vector->vector[i];

  result->signal = num->signal;

  return result;
}

bigInt copyBigInt(bigInt src) {
  if (!src)
    return NULL;

  bigInt dest = initEmpty(*src->size);
  if (!dest)
    return NULL;

  dest->signal = src->signal;
  *dest->size = *src->size;

  if (src->vector && dest->vector) {
    dest->vector->size = src->vector->size;

    memcpy(dest->vector->vector, src->vector->vector,
           *src->size * sizeof(unsigned int));
  }

  return dest;
}

int compareAbs(bigInt a, bigInt b) {
  if (!a || !b)
    return 0;

  if (*a->size > *b->size)
    return 1;
  if (*b->size > *a->size)
    return -1;

  for (int i = (int)(*a->size) - 1; i >= 0; i--) {
    unsigned int digitA = a->vector->vector[i];
    unsigned int digitB = b->vector->vector[i];

    if (digitA > digitB)
      return 1;
    if (digitB > digitA)
      return -1;
  }

  return 0;
}

void appendDigitInPlace(bigInt self, int digit) {
  if (*self->size == 1 && self->vector->vector[0] == 0) {
    self->vector->vector[0] = digit;
    return;
  }

  addFront(self->vector, digit);

  if (self->size != &self->vector->size)
    *self->size = self->vector->size;
}

void removeLeadingZerosBigInt(bigInt self) {
  while (*self->size > 1 && self->vector->vector[*self->size - 1] == 0)
    (*self->size)--;
}
