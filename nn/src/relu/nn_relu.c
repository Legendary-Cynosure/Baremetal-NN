
#include "nn_relu.h"

void NN_ReLU_F16(Tensor *y, Tensor *x) {
  assert(y->ndim == x->ndim);
  assert(x->dtype == DTYPE_F16);
  assert(y->dtype == DTYPE_F16);
  assert(y->size == x->size);

  for (size_t i = 0; i < x->size; i += 1) {
    float16_t val_16 = ((float16_t *)x->data)[i];
    float val = NN_halfToFloat(val_16);
    ((float16_t *)y->data)[i] = val > 0 ? val_16 : 0;
  }
}

void NN_ReLUInplace_F16(Tensor *x) {
  NN_ReLU_F16(x, x);
}

void NN_ReLU_F32(Tensor *y, Tensor *x) {
  assert(y->ndim == x->ndim);
  assert(x->dtype == DTYPE_F32);
  assert(y->dtype == DTYPE_F32);
  assert(y->size == x->size);

  for (size_t i = 0; i < x->size; i += 1) {
    float val = ((float *)x->data)[i];
    ((float *)y->data)[i] = val > 0 ? val : 0;
  }
}

void NN_ReLUInplace_F32(Tensor *x) {
  NN_ReLU_F32(x, x);
}
