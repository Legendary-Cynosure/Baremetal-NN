
#include "minimum.h"


void NN_minimum(Tensor *out, const Tensor *a, const Tensor *b) {
  assert(b->ndim == a->ndim);
  assert(out->ndim == a->ndim);
  assert(b->dtype == a->dtype);
  assert(out->dtype == a->dtype);
  assert(b->size == a->size);
  assert(out->size == a->size);

  switch (out->dtype) {
    case DTYPE_F32:
      NN_minimum_f32(out->size, (float *)out->data, 1, (float *)a->data, 1, (float *)b->data, 1);
      return;

    default:
      break;
  }
  
  printf("[ERROR] Unsupported operation between tensor with dtype %s = max(%s, %s)\n", 
    NN_get_datatype_name(out->dtype), NN_get_datatype_name(a->dtype), NN_get_datatype_name(b->dtype)
  );
}
