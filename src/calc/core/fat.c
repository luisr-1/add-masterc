#include "fat.h"
#include "mult.h"

#define RECURSION_THRESHOLD 15

bigInt binarySplittingProduct(unsigned long long int l,
                              unsigned long long int r) {
  if (r - l < RECURSION_THRESHOLD) {
    if (l > r)
      return intToBigInt(1);
    if (l == r)
      return intToBigInt(l);
  }

  if (l > r)
    return intToBigInt(1);
  if (l == r)
    return intToBigInt(l);

  if (r - l == 1) {
    bigInt bl = intToBigInt(l);
    bigInt br = intToBigInt(r);
    bigInt result = multBigInt(bl, br);
    bl->destroy(bl);
    br->destroy(br);
    return result;
  }

  unsigned long long int mid = l + (r - l) / 2;

  bigInt left_product = binarySplittingProduct(l, mid);
  bigInt right_product = binarySplittingProduct(mid + 1, r);

  if (!left_product || !right_product) {
    if (left_product)
      left_product->destroy(left_product);
    if (right_product)
      right_product->destroy(right_product);
    return NULL;
  }

  bigInt result = multBigInt(left_product, right_product);

  left_product->destroy(left_product);
  right_product->destroy(right_product);

  return result;
}

bigInt factorialBigInt(unsigned int n) {
  if (n <= 1)
    return intToBigInt(1);

  return binarySplittingProduct(1, n);
}
