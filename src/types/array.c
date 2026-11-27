#include "array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

array initArray(size_t size) {
  size_t initial_capacity = (size > 0) ? size : 1;

  array vector = (array)calloc(1, sizeof(struct Array));
  if (!vector) {
    perror("Problema para alocar a estrutura Array");
    return NULL;
  }

  vector->vector =
      (unsigned int *)calloc(initial_capacity, sizeof(unsigned int));
  if (vector->vector == NULL) {
    perror("Problema para alocar o vetor");
    free(vector);
    return NULL;
  }

  vector->capacity = initial_capacity;
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
    fprintf(stderr, "O array é nulo\n");
    return;
  }

  if (self->capacity <= self->size) {
    size_t new_capacity = (self->capacity > 0) ? self->capacity * 2 : 1;
    unsigned int *new_vector = (unsigned int *)realloc(
        self->vector, sizeof(unsigned int) * new_capacity);
    if (!new_vector) {
      perror("Erro ao realocar o vetor");
      return;
    }
    self->vector = new_vector;
    self->capacity = new_capacity;
  }

  self->vector[self->size++] = element;
}

void destroyArray(array self) {
  if (!self)
    return;

  free(self->vector);
  free(self);
}

void removeElement(array self, size_t index) {
  if (isEmpty(self)) {
    fprintf(stderr, "Não existem elementos para remover no array\n");
    return;
  }

  if (index >= self->size) {
    fprintf(stderr, "Índice passado está fora dos limites do array\n");
    return;
  }

  if (index < self->size - 1) {
    memmove(&self->vector[index], &self->vector[index + 1],
            (self->size - index - 1) * sizeof(unsigned int));
  }

  self->size--;
  self->vector[self->size] = 0;

  if (self->capacity > 1 && self->size < (self->capacity / 2)) {
    size_t new_capacity = self->capacity / 2;
    unsigned int *new_vector =
        realloc(self->vector, sizeof(unsigned int) * new_capacity);
    if (new_vector) {
      self->vector = new_vector;
      self->capacity = new_capacity;
    }
  }
}

bool isEmpty(array self) {
  if (!self)
    return true;
  return self->size == 0;
}

void addFront(array self, unsigned int element) {
  if (!self) {
    fprintf(stderr, "O array é nulo\n");
    return;
  }

  if (self->size >= self->capacity) {
    size_t new_capacity = self->capacity * 2 + 1;
    unsigned int *new_vector =
        realloc(self->vector, new_capacity * sizeof(unsigned int));
    if (!new_vector) {
      perror("Erro ao alocar o vetor");
      return;
    }
    self->vector = new_vector;
    self->capacity = new_capacity;
  }

  memmove(self->vector + 1, self->vector, self->size * sizeof(unsigned int));

  self->vector[0] = element;
  self->size++;
}
