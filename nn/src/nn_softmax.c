
#include "nn_softmax.h"


void NN_Softmax(Tensor *out, Tensor *tensor, size_t dim) {
  assert(out->dtype == tensor->dtype);

  switch (tensor->dtype) {
    case DTYPE_F32:
      if (dim == 0) {
        for (size_t i = 0; i < tensor->shape[0]; i += 1) {
          float *x = (float *)tensor->data + i * tensor->shape[1];
          float *y = (float *)out->data + i * out->shape[1];
          NN__softmax_F32(tensor->shape[1], y, x);
        }
        return;
      }
      if (dim == 1) {
        for (size_t i = 0; i < tensor->shape[1]; i += 1) {
          for (size_t j = 0; j < tensor->shape[0]; j += 1) {
            float *x = (float *)tensor->data + j * tensor->shape[1] + i;
            float *y = (float *)out->data + j * out->shape[1] + i;
            NN__softmax_F32(1, y, x);
          }
        }
        return;
      }

      // NN__softmax_F32(tensor->size, (float *)out->data, (float *)tensor->data);
      break;
    
    default:
      printf("[ERROR] Unsupported operation of tensor with dtype %s = softmax(%s)\n", 
        NN_getDataTypeName(out->dtype), NN_getDataTypeName(tensor->dtype)
      );
  }
}
