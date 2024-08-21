#include "impl/acc.h"


__attribute__((weak)) void NN__acc_i8(size_t n, int8_t *y, size_t incy, const int8_t *x, size_t incx) {
  for (size_t i = 0; i < n; i += 1) {
    y[i * incy] += x[i * incx];
  }
}

__attribute__((weak)) void NN__acc_i16(size_t n, int16_t *y, size_t incy, const int16_t *x, size_t incx) {
  for (size_t i = 0; i < n; i += 1) {
    y[i * incy] += x[i * incx];
  }
}

__attribute__((weak)) void NN__acc_i32(size_t n, int32_t *y, size_t incy, const int32_t *x, size_t incx) {
  for (size_t i = 0; i < n; i += 1) {
    y[i * incy] += x[i * incx];
  }
}

__attribute__((weak)) void NN__acc_f16(size_t n, float16_t *y, size_t incy, const float16_t *x, size_t incx) {
  for (size_t i = 0; i < n; i += incx) {
    y[i * incy] = NN_float_to_half(NN_half_to_float(y[i * incy]) + NN_half_to_float(x[i * incx]));
  }
}

__attribute__((weak)) void NN__acc_f32(size_t n, float *y, size_t incy, const float *x, size_t incx) {
  for (size_t i = 0; i < n; i += 1) {
    y[i * incy] += x[i * incx];
  }
}
