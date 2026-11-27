#include "fat.h"
#include "mult.h"

bigInt binarySplittingProduct(unsigned int l, unsigned int r) {
  if (l > r)
    return intToBigInt(1);
  if (l == r)
    return intToBigInt(l);

  if (r - l == 1) {
    bigInt bl = intToBigInt(l);
    bigInt br = intToBigInt(r);
    if (!bl || !br) {
      if (bl)
        bl->destroy(bl);
      if (br)
        br->destroy(br);
      return NULL;
    }
    bigInt result = multBigInt(bl, br);
    bl->destroy(bl);
    br->destroy(br);
    return result;
  }

  unsigned int mid = l + (r - l) / 2;

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
