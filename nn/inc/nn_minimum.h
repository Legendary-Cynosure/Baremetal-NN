#ifndef __NN_MINIMUM_H
#define __NN_MINIMUM_H

#include <assert.h>
#ifdef RVV
  #include <riscv_vector.h>
#endif

#include "nn_tensor.h"
#include "ops/minimum.h"


/**
 * Computes the element-wise minimum of two tensors.
 * 
 * @param out: the output tensor
 * @param a: the input tensor
 * @param b: the input tensor
 */
void NN_minimum(Tensor *out, Tensor *a, Tensor *b);


#endif // __NN_MINIMUM_H
