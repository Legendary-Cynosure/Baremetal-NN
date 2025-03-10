#ifndef __NN_NORM_H
#define __NN_NORM_H

#include <assert.h>
#include <math.h>

#include "tensor.h"


/**
 * Computes the Frobenius norm of a matrix.
 * 
 * @param tensor: the input tensor of shape (m, n)
 */
void NN_norm(Tensor *scalar, const Tensor *x);


#endif // __NN_NORM_H
