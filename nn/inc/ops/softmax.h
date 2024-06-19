#ifndef __NN__SOFTMAX_H
#define __NN__SOFTMAX_H

#include <stddef.h>
#include <math.h>

#ifdef RVV
  #include <riscv_vector.h>
#endif

static inline void NN__softmax_F32(size_t n, float *y, float *x) {
  // find max value (for numerical stability)
  float max_val = x[0];
  for (int i = 1; i < n; i += 1) {
      if (x[i] > max_val) {
          max_val = x[i];
      }
  }
  // exp and sum
  float sum = 0.0f;
  for (int i = 0; i < n; i += 1) {
      y[i] = expf(x[i] - max_val);
      sum += y[i];
  }
  // normalize
  for (int i = 0; i < n; i += 1) {
      y[i] /= sum;
  }
}


#endif // __NN__SOFTMAX_H
