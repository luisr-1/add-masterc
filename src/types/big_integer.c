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
    fprintf(stderr, "A string passada é nula, o número não será inicializado\n");
    return NULL;
  }

  char *num_sanitized = sanitizeNumber(num);
  if (!num_sanitized) {
    fprintf(stderr, "Problema na limpeza da string de representação numérica\n");
    return NULL;
  }

  bigInt n = (bigInt)calloc(1, sizeof(struct BigInteger));
  if (!n) {
    perror("Ocorreu um problema para alocar espaço para o BigInt");
    free(num_sanitized);
    return NULL;
  }

  n->destroy = destroyBigInt;
  n->init = initNumber;
  n->newBigInt = initEmpty;
  n->to_decimal_representation = toDecimalRepresentation;

  size_t i = 0;

  if (num_sanitized[0] == '-') {
    n->signal = -1;
    i = 1;
  } else {
    n->signal = 1;
    if (num_sanitized[0] == '+')
      i = 1;
  }

  size_t max_length = strlen(num_sanitized);
  size_t sizeNum = max_length - i;

  n->vector = initArray(sizeNum);
  if (!n->vector) {
    fprintf(stderr, "Erro ao alocar o vetor dinâmico para os dígitos\n");
    destroyBigInt(n);
    free(num_sanitized);
    return NULL;
  }

  n->size = &n->vector->size;

  for (; i < max_length; i++) {
    if (!isdigit((unsigned char)num_sanitized[i])) {
      fprintf(stderr,
              "Caractere inválido encontrado na string de inicialização\n");
      destroyBigInt(n);
      free(num_sanitized);
      return NULL;
    }
    n->vector->add_front(n->vector, (unsigned int)charToInt(num_sanitized[i]));
  }

  free(num_sanitized);
  return n;
}

char *sanitizeNumber(const char *number) {
  if (!number)
    return NULL;

  size_t i = 0;
  while (isspace((unsigned char)number[i]))
    i++;

  size_t minus_count = 0;
  while (number[i] == '+' || number[i] == '-') {
    if (number[i] == '-')
      minus_count++;
    i++;
  }

  bool has_zero = false;
  while (number[i] == '0') {
    has_zero = true;
    i++;
  }

  size_t end = strlen(number);
  while (end > i && isspace((unsigned char)number[end - 1]))
    end--;

  if (i == end) {
    if (!has_zero)
      return NULL;

    char *zero = (char *)calloc(2, sizeof(char));
    if (!zero)
      return NULL;
    strcpy(zero, "0");
    return zero;
  }

  char signal = 0;
  if (minus_count % 2 == 1)
    signal = '-';

  size_t body_len = end - i;
  size_t total_len = body_len + (signal ? 1 : 0) + 1;

  char *sanitized = (char *)calloc(total_len, sizeof(char));
  if (!sanitized)
    return NULL;

  size_t position = 0;
  if (signal)
    sanitized[position++] = signal;

  memcpy(&sanitized[position], number + i, body_len);
  sanitized[position + body_len] = '\0';

  return sanitized;
}

char *toDecimalRepresentation(bigInt b) {
  if (!b || !b->vector) {
    fprintf(stderr,
            "Número passado é nulo, não tem como ser realizada a conversão\n");
    return NULL;
  }

  if (*b->size == 0) {
    char *zero = (char *)calloc(2, sizeof(char));
    if (zero)
      strcpy(zero, "0");
    return zero;
  }

  int has_signal = (b->signal == -1);

  size_t total_len = *b->size + (size_t)has_signal + 1;
  char *out = (char *)calloc(total_len, sizeof(char));
  if (!out) {
    perror("Erro na alocação da string para representação numérica");
    return NULL;
  }

  size_t position = 0;

  if (has_signal)
    out[position++] = '-';

  for (size_t i = *b->size; i > 0; i--)
    out[position++] = intToChar((int)b->vector->vector[i - 1]);

  out[position] = '\0';

  char *sanitized = sanitizeNumber(out);
  free(out);
  return sanitized;
}

void destroyBigInt(bigInt b) {
  if (!b)
    return;

  if (b->vector)
    b->vector->destroy(b->vector);

  free(b);
}

bigInt initEmpty(const unsigned int size) {
  if (size == 0)
    return NULL;

  bigInt b = (bigInt)calloc(1, sizeof(struct BigInteger));
  if (!b) {
    perror("Erro ao alocar bigInt vazio");
    return NULL;
  }

  b->vector = initArray(size);
  if (!b->vector) {
    fprintf(stderr, "Erro ao inicializar o array de dígitos\n");
    free(b);
    return NULL;
  }

  b->size = &b->vector->size;
  b->signal = 1;
  b->destroy = destroyBigInt;
  b->to_decimal_representation = toDecimalRepresentation;
  b->init = initNumber;
  b->newBigInt = initEmpty;

  return b;
}

bigInt intToBigInt(unsigned int n) {
  char buffer[128];
  snprintf(buffer, sizeof(buffer), "%u", n);
  return initNumber(buffer);
}

bigInt shiftLeftBigInt(bigInt num, int positions) {
  if (!num || !num->vector || positions < 0)
    return NULL;

  if (positions == 0)
    return copyBigInt(num);

  if (*num->size == 1 && num->vector->vector[0] == 0)
    return intToBigInt(0);

  size_t new_size = *num->size + (size_t)positions;
  bigInt result = initEmpty((unsigned int)new_size);
  if (!result)
    return NULL;

  for (int i = 0; i < positions; i++)
    result->vector->vector[i] = 0;

  for (size_t i = 0; i < *num->size; i++)
    result->vector->vector[i + (size_t)positions] = num->vector->vector[i];

  *result->size = new_size;
  result->signal = num->signal;
  removeLeadingZerosBigInt(result);

  return result;
}

bigInt copyBigInt(bigInt src) {
  if (!src || !src->vector)
    return NULL;

  size_t cap = (*src->size > 0) ? *src->size : 1;
  bigInt dest = initEmpty((unsigned int)cap);
  if (!dest)
    return NULL;

  dest->signal = src->signal;
  *dest->size = *src->size;

  if (*src->size > 0) {
    memcpy(dest->vector->vector, src->vector->vector,
           *src->size * sizeof(unsigned int));
  }

  return dest;
}

int compareAbs(bigInt a, bigInt b) {
  if (!a || !b || !a->vector || !b->vector)
    return 0;

  size_t lenA = *a->size;
  size_t lenB = *b->size;

  while (lenA > 1 && a->vector->vector[lenA - 1] == 0)
    lenA--;
  while (lenB > 1 && b->vector->vector[lenB - 1] == 0)
    lenB--;

  if (lenA > lenB)
    return 1;
  if (lenB > lenA)
    return -1;

  for (size_t idx = lenA; idx > 0; idx--) {
    unsigned int digitA = a->vector->vector[idx - 1];
    unsigned int digitB = b->vector->vector[idx - 1];

    if (digitA > digitB)
      return 1;
    if (digitB > digitA)
      return -1;
  }

  return 0;
}

void appendDigitInPlace(bigInt self, int digit) {
  if (!self || !self->vector)
    return;

  if (*self->size == 0) {
    self->vector->add(self->vector, (unsigned int)digit);
    return;
  }

  if (*self->size == 1 && self->vector->vector[0] == 0) {
    self->vector->vector[0] = (unsigned int)digit;
    return;
  }

  addFront(self->vector, (unsigned int)digit);
}

void removeLeadingZerosBigInt(bigInt self) {
  if (!self || !self->vector)
    return;

  while (*self->size > 1 && self->vector->vector[*self->size - 1] == 0) {
    self->vector->remove(self->vector, *self->size - 1);
  }

  if (*self->size == 1 && self->vector->vector[0] == 0) {
    self->signal = 1;
  }
}
