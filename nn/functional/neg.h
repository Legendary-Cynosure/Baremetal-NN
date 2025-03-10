#ifndef __NN_NEG_H
#define __NN_NEG_H

#include <assert.h>

#include "tensor.h"
#include "ops/neg.h"


/**
 * Returns a tensor with the negative of the elements of input.
 * 
 * out = -1 x input
 * 
 * @param out: the output tensor
 * @param input: the input tensor
 */
void NN_neg(Tensor *out, const Tensor *input);

void NN_neg_inplace(Tensor *tensor);


#endif // __NN_NEG_H
