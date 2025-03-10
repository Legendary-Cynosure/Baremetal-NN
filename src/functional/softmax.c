
#include "softmax.h"


void NN_softmax(Tensor *out, const Tensor *tensor, int dim) {
  assert(out->dtype == tensor->dtype);

  if (dim < 0) {
    dim = out->ndim + dim;
  }

  switch (tensor->dtype) {
    case DTYPE_F32:
      if (dim == 0) {
        for (size_t i = 0; i < tensor->shape[1]; i += 1) {
          float *x = (float *)tensor->data + i;
          float *y = (float *)out->data + i;
          NN_softmax_f32(tensor->shape[0], y, tensor->shape[1], x, tensor->shape[1]);
        }
        return;
      }
      if (dim == 1) {
        for (size_t i = 0; i < tensor->shape[0]; i += 1) {
          float *x = (float *)tensor->data + i * tensor->shape[1];
          float *y = (float *)out->data + i * out->shape[1];
          NN_softmax_f32(tensor->shape[1], y, 1, x, 1);
        }
        return;
      }
      break;
    
    default:
      printf("[ERROR] Unsupported operation of tensor with dtype %s = softmax(%s)\n", 
        NN_get_datatype_name(out->dtype), NN_get_datatype_name(tensor->dtype)
      );
  }
}
