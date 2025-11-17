#include "array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

array initArray(unsigned int size) {
  array vector = (array)malloc(sizeof(struct Array));
  if (vector == NULL) {
    perror("Problema para a estrutura Array\n");
    return NULL;
  }

  vector->vector = (unsigned int *)malloc(sizeof(unsigned int) * size);
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

  return vector;
}

void addElement(array self, unsigned int element) {
  if (self == NULL) {
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

void removeElement(array self, unsigned int index) {
  if (self == NULL || self->is_empty(self)) {
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
  if (self == NULL)
    return true;
  else if (self->size == 0)
    return true;
  else
    return false;
}