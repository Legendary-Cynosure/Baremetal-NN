#include <riscv_vector.h>
#include "kernel/acc.h"

#ifdef RVV

void NN_acc_i8(size_t n, int8_t *y, size_t incy, const int8_t *x, size_t incx) {
  while (n > 0) {
    size_t vl = __riscv_vsetvl_e8m1(n);
    vint8m1_t vec_x = __riscv_vlse8_v_i8m1(x, sizeof(int8_t) * incx, vl);
    vint8m1_t vec_y = __riscv_vlse8_v_i8m1(y, sizeof(int8_t) * incy, vl);
    vec_y = __riscv_vadd_vv_i8m1(vec_y, vec_x, vl);
    __riscv_vsse8_v_i8m1(y, sizeof(int8_t) * incy, vec_y, vl);
    x += vl;
    y += vl;
    n -= vl;
  }
}

void NN_acc_i16(size_t n, int16_t *y, size_t incy, const int16_t *x, size_t incx) {
  while (n > 0) {
    size_t vl = __riscv_vsetvl_e16m1(n);
    vint16m1_t vec_x = __riscv_vlse16_v_i16m1(x, sizeof(int16_t) * incx, vl);
    vint16m1_t vec_y = __riscv_vlse16_v_i16m1(y, sizeof(int16_t) * incy, vl);
    vec_y = __riscv_vadd_vv_i16m1(vec_y, vec_x, vl);
    __riscv_vsse16_v_i16m1(y, sizeof(int16_t) * incy, vec_y, vl);
    x += vl;
    y += vl;
    n -= vl;
  }
}

void NN_acc_i32(size_t n, int32_t *y, size_t incy, const int32_t *x, size_t incx) {
  while (n > 0) {
    size_t vl = __riscv_vsetvl_e32m1(n);
    vint32m1_t vec_x = __riscv_vlse32_v_i32m1(x, sizeof(int32_t) * incx, vl);
    vint32m1_t vec_y = __riscv_vlse32_v_i32m1(y, sizeof(int32_t) * incy, vl);
    vec_y = __riscv_vadd_vv_i32m1(vec_y, vec_x, vl);
    __riscv_vsse32_v_i32m1(y, sizeof(int32_t) * incy, vec_y, vl);
    x += vl;
    y += vl;
    n -= vl;
  }
}

#ifdef RISCV_ZVFH
  void NN_acc_f16(size_t n, float16_t *y, size_t incy, const float16_t *x, size_t incx) {
    while (n > 0) {
      size_t vl = __riscv_vsetvl_e16m1(n);
      vfloat16m1_t vec_x = __riscv_vlse16_v_f16m1(x, sizeof(float16_t) * incx, vl);
      vfloat16m1_t vec_y = __riscv_vlse16_v_f16m1(y, sizeof(float16_t) * incy, vl);
      vec_y = __riscv_vfadd_vv_f16m1(vec_y, vec_x, vl);
      __riscv_vsse16_v_f16m1(y, sizeof(float16_t) * incy, vec_y, vl);
      x += vl;
      y += vl;
      n -= vl;
    }
  }
#endif

void NN_acc_f32(size_t n, float *y, size_t incy, const float *x, size_t incx) {
  while (n > 0) {
    size_t vl = __riscv_vsetvl_e32m1(n);
    vfloat32m1_t vec_x = __riscv_vlse32_v_f32m1(x, sizeof(float) * incx, vl);
    vfloat32m1_t vec_y = __riscv_vlse32_v_f32m1(y, sizeof(float) * incy, vl);
    vec_y = __riscv_vfadd_vv_f32m1(vec_y, vec_x, vl);
    __riscv_vsse32_v_f32m1(y, sizeof(float) * incy, vec_y, vl);
    x += vl;
    y += vl;
    n -= vl;
  }
}

#endif
