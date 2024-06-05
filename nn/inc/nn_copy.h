#ifndef __NN_COPY_H
#define __NN_COPY_H

#include "nn_tensor.h"


/**
 * Copies values from one tensor to another
 * 
 * @param dst: destination tensor
 * @param src: source tensor
 */
void NN_copy(Tensor *dst, Tensor *src);


#endif // __NN_COPY_H
