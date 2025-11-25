#include "array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

array initArray(size_t size) {
  array vector = (array)calloc(size, sizeof(struct Array));
  if (!vector) {
    perror("Problema para a estrutura Array\n");
    return NULL;
  }

  vector->vector = (unsigned int *)calloc(size, sizeof(unsigned int));
  if (vector->vector == NULL) {
    perror("Problema para alocar o vetor\n");
    return NULL;
  }

  vector->capacity = size;
  vector->size = 0;
  vector->add = addElement;
  vector->remove = removeElement;
  vector->is_empty = isEmpty;
  vector->destroy = destroyArray;
  vector->add_front = addFront;

  return vector;
}

void addElement(array self, unsigned int element) {
  if (!self) {
    perror("O array é nulo\n");
    return;
  }

  if (self->capacity <= self->size) {
    self->capacity *= 2;
    self->vector = (unsigned int *)realloc(self->vector, sizeof(unsigned int) *
                                                             self->capacity);
  }

  self->vector[self->size++] = element;
}

void destroyArray(array self) {
  free(self->vector);
  free(self);
}

void removeElement(array self, size_t index) {
  if (isEmpty(self)) {
    perror("Não existem elementos para remover no array\n");
    return;
  }

  if (index > self->size) {
    perror("Indice passado está fora da capacidade do array\n");
    return;
  }

  self->vector[self->size--] = 0;
  if (self->size < (self->capacity / 2)) {
    self->capacity /= 2;
    self->vector = realloc(self->vector, sizeof(unsigned int) * self->capacity);
  }
}

bool isEmpty(array self) {
  if (!self)
    return true;
  else if (self->size == 0)
    return true;
  else
    return false;
}

void addFront(array self, unsigned int element) {
  if (self->size == self->capacity) {
    size_t new_capacity = self->capacity * 2 + 1;
    unsigned int *new_vector =
        realloc(self->vector, new_capacity * sizeof(unsigned int));
    if (!new_vector) {
      perror("Erro ao alocar o vetor\n");
      return;
    }
    self->vector = new_vector;
    self->capacity = new_capacity;
  }

  memmove(self->vector + 1, self->vector, self->size * sizeof(unsigned int));

  self->vector[0] = element;
  self->size++;
}
