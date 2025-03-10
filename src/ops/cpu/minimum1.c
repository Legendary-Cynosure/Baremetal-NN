#include "ops/minimum1.h"


__attribute__((weak)) void NN_minimum1_i8(size_t n, int8_t *y, size_t incy, const int8_t *x, size_t incx, int8_t s) {
  for (size_t i = 0; i < n; i += 1) {
    y[i * incy] = x[i * incx] < s ? x[i * incx] : s;
  }
}

__attribute__((weak)) void NN_minimum1_i16(size_t n, int16_t *y, size_t incy, const int16_t *x, size_t incx, int16_t s) {
  for (size_t i = 0; i < n; i += 1) {
    y[i * incy] = x[i * incx] < s ? x[i * incx] : s;
  }
}

__attribute__((weak)) void NN_minimum1_i32(size_t n, int32_t *y, size_t incy, const int32_t *x, size_t incx, int32_t s) {
  for (size_t i = 0; i < n; i += 1) {
    y[i * incy] = x[i * incx] < s ? x[i * incx] : s;
  }
}

__attribute__((weak)) void NN_minimum1_f16(size_t n, float16_t *y, size_t incy, const float16_t *x, size_t incx, float16_t s) {
  for (size_t i = 0; i < n; i += 1) {
    float16_t x_val = x[i * incx];
    y[i * incy] = NN_half_to_float(x_val) < NN_half_to_float(s) ? x_val : s;
  }
}

__attribute__((weak)) void NN_minimum1_f32(size_t n, float *y, size_t incy, const float *x, size_t incx, float s) {
  for (size_t i = 0; i < n; i += 1) {
    float x_val = x[i * incx];
    y[i * incy] = x_val < s ? x_val : s;
  }
}

