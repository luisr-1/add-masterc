#ifndef ARRAY_H
#define ARRAY_H

#include "stdbool.h"
#include <stdio.h>

// array is a pointer to Array struct
typedef struct Array *array;

// Functions pointers to
typedef array (*Init)(unsigned int size);
typedef bool (*Empty)(array self);
typedef void (*Add)(array self, unsigned int element);
typedef void (*Remove)(array self, unsigned int index);

/**
 * @brief: The basic structure of a dynamic array of unsigned int
 * @param vector -> Pointer to hold the elements of array
 * @param capacity -> Number of elements the array can hold in the current time
 * @param size -> Current total of elements hold by array
 * @param init -> pointer to function initArray;
 * @param is_empty -> pointer to function isEmpty;
 * @param remove -> pointer to function removeElement;
 * @param add -> pointer to function addElement;
 **/
struct Array {
  unsigned int *vector;
  size_t capacity;
  size_t size;

  Init init;
  Empty is_empty;
  Remove remove;
  Add add;
};

/**
 * @brief: Is the constructor of array, given size n, returns an array
 * initialized with n positions
 * @param size -> the initial size of array
 */
array initArray(unsigned int size);

/**
 * @param self -> Pointer to array itself
 * @param n -> The element to be added to array
 */
void addElement(array self, unsigned int n);

/**
 * @param self -> Pointer to array itself
 * @param index -> The position of the item to be removed of array
 */
void removeElement(array self, unsigned int index);

/**
 * @param self -> Pointer to array itself
 * @return true -> size == 0 || self == NULL
 * @return false -> size > 0
 */
bool isEmpty(array self);

#endif