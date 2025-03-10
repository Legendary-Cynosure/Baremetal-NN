#include <riscv_vector.h>
#include "ops/min.h"

#ifdef RVV

void NN_min_i8(size_t n, int8_t *r, const int8_t *x, size_t incx) {
  vint8m1_t vec_max = __riscv_vmv_v_x_i8m1(INT8_MIN, 1);
  while (n > 0) {
    size_t vl = __riscv_vsetvl_e8m1(n);
    vint8m1_t vec_x = __riscv_vlse8_v_i8m1(x, sizeof(int8_t) * incx, vl);
    vec_max = __riscv_vredmin_vs_i8m1_i8m1(vec_x, vec_max, vl);
    x += vl;
    n -= vl;
  }
  *r = __riscv_vmv_x_s_i8m1_i8(vec_max);
}

void NN_min_i16(size_t n, int16_t *r, const int16_t *x, size_t incx) {
  vint16m1_t vec_max = __riscv_vmv_v_x_i16m1(INT16_MIN, 1);
  while (n > 0) {
    size_t vl = __riscv_vsetvl_e16m1(n);
    vint16m1_t vec_x = __riscv_vlse16_v_i16m1(x, sizeof(int16_t) * incx, vl);
    vec_max = __riscv_vredmin_vs_i16m1_i16m1(vec_x, vec_max, vl);
    x += vl;
    n -= vl;
  }
  *r = __riscv_vmv_x_s_i16m1_i16(vec_max);
}

void NN_min_i32(size_t n, int32_t *r, const int32_t *x, size_t incx) {
  vint32m1_t vec_max = __riscv_vmv_v_x_i32m1(INT32_MIN, 1);
  while (n > 0) {
    size_t vl = __riscv_vsetvl_e32m1(n);
    vint32m1_t vec_x = __riscv_vlse32_v_i32m1(x, sizeof(int32_t) * incx, vl);
    vec_max = __riscv_vredmin_vs_i32m1_i32m1(vec_x, vec_max, vl);
    x += vl;
    n -= vl;
  }
  *r = __riscv_vmv_x_s_i32m1_i32(vec_max);
}

#ifdef RISCV_ZVFH
  void NN_min_f16(size_t n, float16_t *r, const float16_t *x, size_t incx) {
    vfloat16m1_t vec_max = __riscv_vfmv_v_f_f16m1(-FLT_MAX, 1);
    while (n > 0) {
      size_t vl = __riscv_vsetvl_e16m1(n);
      vfloat16m1_t vec_x = __riscv_vlse16_v_f16m1(x, sizeof(float16_t) * incx, vl);
      vec_max = __riscv_vfredmin_vs_f16m1_f16m1(vec_x, vec_max, vl);
      x += vl;
      n -= vl;
    }
    *r = __riscv_vfmv_f_s_f16m1_f16(vec_max);
  }
#endif

void NN_min_f32(size_t n, float *r, const float *x, size_t incx) {
  vfloat32m1_t vec_min = __riscv_vfmv_s_f_f32m1(FLT_MAX, 1);
  while (n > 0) {
    size_t vl = __riscv_vsetvl_e32m1(n);
    vfloat32m1_t vec_x = __riscv_vlse32_v_f32m1(x, sizeof(float) * incx, vl);
    vec_min = __riscv_vfredmin_vs_f32m1_f32m1(vec_x, vec_min, vl);
    x += vl;
    n -= vl;
  }
  *r = __riscv_vfmv_f_s_f32m1_f32(vec_min);
}


#endif
