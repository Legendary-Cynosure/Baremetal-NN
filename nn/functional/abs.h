#ifndef __NN_ABS_H
#define __NN_ABS_H

#include <assert.h>

#include "tensor.h"
#include "ops/abs.h"


/**
 * Computes the absolute value of each element in input.
 * 
 * out_i = |input_i|
 * 
 * @param out: the output tensor
 * @param input: the input tensor
 */
void NN_abs(Tensor *out, const Tensor *input);

void NN_abs_inplace(Tensor *x);


#endif // __NN_ABS_H
