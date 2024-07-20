#ifndef __NN_RELU6_H
#define __NN_RELU6_H

#include <assert.h>

#include "nn_tensor.h"
#include "impl/maximum1.h"
#include "impl/minimum1.h"


/**
 * Applies the ReLU6 function element-wise.
 * 
 * y = ReLU6(x) = min(max(x, 0), 6)
 * 
 * @param y: the output tensor
 * @param x: the input tensor
 */
void NN_relu6(Tensor *y, const Tensor *x);

void NN_relu6_inplace(Tensor *x);


#endif // __NN_RELU6_H
