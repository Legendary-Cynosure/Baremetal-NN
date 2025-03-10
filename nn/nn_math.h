#ifndef __NN_MATH_H
#define __NN_MATH_H


#include <assert.h>
#include <math.h>
#include <string.h>

#include "float16.h"

//
// fundamental operations
//



// inline static void NN_mad_F32(const int n, float *y, const float *x, const float v) {
// #if defined(GGML_SIMD)
//     const int np = (n & ~(GGML_F32_STEP - 1));

//     GGML_F32_VEC vx = GGML_F32_VEC_SET1(v);

//     GGML_F32_VEC ax[GGML_F32_ARR];
//     GGML_F32_VEC ay[GGML_F32_ARR];

//     for (int i = 0; i < np; i += GGML_F32_STEP) {
//         for (int j = 0; j < GGML_F32_ARR; j++) {
//             ax[j] = GGML_F32_VEC_LOAD(x + i + j*GGML_F32_EPR);
//             ay[j] = GGML_F32_VEC_LOAD(y + i + j*GGML_F32_EPR);
//             ay[j] = GGML_F32_VEC_FMA(ay[j], ax[j], vx);

//             GGML_F32_VEC_STORE(y + i + j*GGML_F32_EPR, ay[j]);
//         }
//     }

//     // leftovers
//     for (int i = np; i < n; i += 1) {
//         y[i] += x[i]*v;
//     }
// #else
//     // scalar
//     for (int i = 0; i < n; i += 1) {
//         y[i] += x[i]*v;
//     }
// #endif
// }

// inline static void NN_mad_f16(const int n, float16_t *y, const float16_t *x, const float v) {
// #if defined(GGML_SIMD)
//     const int np = (n & ~(GGML_F16_STEP - 1));

//     GGML_F16_VEC vx = GGML_F16_VEC_SET1(v);

//     GGML_F16_VEC ax[GGML_F16_ARR];
//     GGML_F16_VEC ay[GGML_F16_ARR];

//     for (int i = 0; i < np; i += GGML_F16_STEP) {
//         for (int j = 0; j < GGML_F16_ARR; j++) {
//             ax[j] = GGML_F16_VEC_LOAD(x + i + j*GGML_F16_EPR, j);
//             ay[j] = GGML_F16_VEC_LOAD(y + i + j*GGML_F16_EPR, j);
//             ay[j] = GGML_F16_VEC_FMA(ay[j], ax[j], vx);

//             GGML_F16_VEC_STORE(y + i + j*GGML_F16_EPR, ay, j);
//         }
//     }

//     // leftovers
//     for (int i = np; i < n; i += 1) {
//         y[i] = GGML_FP32_TO_FP16(GGML_FP16_TO_FP32(y[i]) + GGML_FP16_TO_FP32(x[i])*v);
//     }
// #else
//     // scalar
//     for (int i = 0; i < n; i += 1) {
//         y[i] = GGML_FP32_TO_FP16(GGML_FP16_TO_FP32(y[i]) + GGML_FP16_TO_FP32(x[i])*v);
//     }
// #endif
// }

// // xs and vs are byte strides of x and v
// inline static void NN_mad_F32_unroll(const int n, const int xs, const int vs, float *restrict y, const float *restrict xv, const float *restrict vv) {

//     const float *restrict x[GGML_VEC_MAD_UNROLL];
//     const float *restrict v[GGML_VEC_MAD_UNROLL];

//     for (int i = 0; i < GGML_VEC_MAD_UNROLL; i += 1) {
//         x[i] = (const float *) ((const char *) xv + i*xs);
//         v[i] = (const float *) ((const char *) vv + i*vs);
//     }

// #if defined(GGML_SIMD)
//     const int np = (n & ~(GGML_F32_STEP - 1));

//     GGML_F32_VEC vx[GGML_VEC_MAD_UNROLL];

//     for (int k = 0; k < GGML_VEC_MAD_UNROLL; ++k) {
//         vx[k] = GGML_F32_VEC_SET1(v[k][0]);
//     }

//     GGML_F32_VEC ax[GGML_VEC_MAD_UNROLL][GGML_F32_ARR];
//     GGML_F32_VEC ay[GGML_F32_ARR];

//     for (int i = 0; i < np; i += GGML_F32_STEP) {
//         for (int j = 0; j < GGML_F32_ARR; j++) {
//             ay[j] = GGML_F32_VEC_LOAD(y + i + j*GGML_F32_EPR);

//             for (int k = 0; k < GGML_VEC_MAD_UNROLL; ++k) {
//                 ax[k][j] = GGML_F32_VEC_LOAD(x[k] + i + j*GGML_F32_EPR);
//                 ay[j] = GGML_F32_VEC_FMA(ay[j], ax[k][j], vx[k]);
//             }

//             GGML_F32_VEC_STORE(y + i + j*GGML_F32_EPR, ay[j]);
//         }
//     }

//     // leftovers
//     for (int k = 0; k < GGML_VEC_MAD_UNROLL; ++k) {
//         for (int i = np; i < n; i += 1) {
//             y[i] += x[k][i]*v[k][0];
//         }
//     }
// #else
//     // scalar
//     for (int k = 0; k < GGML_VEC_MAD_UNROLL; ++k) {
//         for (int i = 0; i < n; i += 1) {
//             y[i] += x[k][i]*v[k][0];
//         }
//     }
// #endif
// }

// inline static void NN_step_F32 (const int n, float *y, const float *x) { for (int i = 0; i < n; i += 1) y[i] = (x[i] > 0.f) ? 1.f : 0.f; }
// inline static void NN_tanh_F32 (const int n, float *y, const float *x) { for (int i = 0; i < n; i += 1) y[i] = tanhf(x[i]);  }
// inline static void NN_elu_F32  (const int n, float *y, const float *x) { for (int i = 0; i < n; i += 1) y[i] = (x[i] > 0.f) ? x[i] : expf(x[i])-1; }
// inline static void NN_relu_F32 (const int n, float *y, const float *x) { for (int i = 0; i < n; i += 1) y[i] = (x[i] > 0.f) ? x[i] : 0.f; }
// inline static void NN_leaky_relu_F32 (const int n, float *y, const float *x, const float ns) { for (int i = 0; i < n; i += 1) y[i] = ((x[i] > 0.f) ? x[i] : 0.f) + ns * ((x[i] < 0.0f) ? x[i] : 0.f); }
// inline static void NN_sigmoid_F32 (const int n, float *y, const float *x) { for (int i = 0; i < n; i += 1) y[i] = 1.f / (1.f + expf(-x[i])); }
// // TODO: optimize performance
// inline static void NN_hardswish_F32 (const int n, float *y, const float *x) { for (int i = 0; i < n; i += 1) y[i] = x[i] * fminf(1.0f, fmaxf(0.0f, (x[i] + 3.0f) / 6.0f)); }
// inline static void NN_hardsigmoid_F32 (const int n, float *y, const float *x) { for (int i = 0; i < n; i += 1) y[i] = fminf(1.0f, fmaxf(0.0f, (x[i] + 3.0f) / 6.0f)); }

// static const float GELU_COEF_A     = 0.044715f;
// static const float GELU_QUICK_COEF = -1.702f;
// static const float SQRT_2_OVER_PI  = 0.79788456080286535587989211986876f;

// inline static float ggml_gelu_F32(float x) {
//     return 0.5f*x*(1.0f + tanhf(SQRT_2_OVER_PI*x*(1.0f + GELU_COEF_A*x*x)));
// }

// inline static void NN_gelu_f16(const int n, float16_t * y, const float16_t * x) {
//     const uint16_t * i16 = (const uint16_t *) x;
//     for (int i = 0; i < n; i += 1) {
//         y[i] = ggml_table_gelu_f16[i16[i]];
//     }
// }

// #ifdef GGML_GELU_FP16
// inline static void NN_gelu_F32(const int n, float *y, const float *x) {
//     uint16_t t;
//     for (int i = 0; i < n; i += 1) {
//         if (x[i] <= -10.0f) {
//             y[i] = 0.0f;
//         } else if (x[i] >= 10.0f) {
//             y[i] = x[i];
//         } else {
//             float16_t fp16 = GGML_FP32_TO_FP16(x[i]);
//             memcpy(&t, &fp16, sizeof(uint16_t));
//             y[i] = GGML_FP16_TO_FP32(ggml_table_gelu_f16[t]);
//         }
//     }
// }
// #else
// inline static void NN_gelu_F32(const int n, float *y, const float *x) {
//     for (int i = 0; i < n; i += 1) {
//         y[i] = ggml_gelu_F32(x[i]);
//     }
// }
// #endif

// inline static float ggml_gelu_quick_F32(float x) {
//     return x*(1.0f/(1.0f+expf(GELU_QUICK_COEF*x)));
// }

// //inline static void NN_gelu_quick_f16(const int n, float16_t * y, const float16_t * x) {
// //    const uint16_t * i16 = (const uint16_t *) x;
// //    for (int i = 0; i < n; i += 1) {
// //        y[i] = ggml_table_gelu_quick_f16[i16[i]];
// //    }
// //}

// #ifdef GGML_GELU_QUICK_FP16
// inline static void NN_gelu_quick_F32(const int n, float *y, const float *x) {
//     uint16_t t;
//     for (int i = 0; i < n; i += 1) {
//         float16_t fp16 = GGML_FP32_TO_FP16(x[i]);
//         memcpy(&t, &fp16, sizeof(uint16_t));
//         y[i] = GGML_FP16_TO_FP32(ggml_table_gelu_quick_f16[t]);
//     }
// }
// #else
// inline static void NN_gelu_quick_F32(const int n, float *y, const float *x) {
//     for (int i = 0; i < n; i += 1) {
//         y[i] = ggml_gelu_quick_F32(x[i]);
//     }
// }
// #endif

// // Sigmoid Linear Unit (SiLU) function
// inline static float ggml_silu_F32(float x) {
//     return x/(1.0f + expf(-x));
// }

// #if defined(__ARM_NEON) && defined(__aarch64__)

// // adapted from arm limited optimized routine
// // the maximum error is 1.45358 plus 0.5 ulps
// // numbers above 88.38 will flush to infinity
// // numbers beneath -103.97 will flush to zero
// inline static float32x4_t ggml_v_expf(float32x4_t x) {
//     const float32x4_t r = vdupq_n_F32(0x1.8p23f);
//     const float32x4_t z = vfmaq_F32(r, x, vdupq_n_F32(0x1.715476p+0f));
//     const float32x4_t n = vsubq_F32(z, r);
//     const float32x4_t b = vfmsq_F32(vfmsq_F32(x, n, vdupq_n_F32(0x1.62e4p-1f)), n,
//                                     vdupq_n_F32(0x1.7f7d1cp-20f));
//     const uint32x4_t e = vshlq_n_u32(vreinterpretq_u32_F32(z), 23);
//     const float32x4_t k = vreinterpretq_F32_u32(vaddq_u32(e, vreinterpretq_u32_F32(vdupq_n_F32(1))));
//     const uint32x4_t c = vcagtq_F32(n, vdupq_n_F32(126));
//     const float32x4_t u = vmulq_F32(b, b);
//     const float32x4_t j = vfmaq_F32(
//         vmulq_F32(vdupq_n_F32(0x1.ffffecp-1f), b),
//         vfmaq_F32(vfmaq_F32(vdupq_n_F32(0x1.fffdb6p-2f), vdupq_n_F32(0x1.555e66p-3f), b),
//                   vfmaq_F32(vdupq_n_F32(0x1.573e2ep-5f), vdupq_n_F32(0x1.0e4020p-7f), b), u), u);
//     if (!vpaddd_u64(vreinterpretq_u64_u32(c)))
//         return vfmaq_F32(k, j, k);
//     const uint32x4_t d = vandq_u32(vclezq_F32(n), vdupq_n_u32(0x82000000));
//     const float32x4_t s1 = vreinterpretq_F32_u32(vaddq_u32(d, vdupq_n_u32(0x7f000000)));
//     const float32x4_t s2 = vreinterpretq_F32_u32(vsubq_u32(e, d));
//     return vbslq_F32(vcagtq_F32(n, vdupq_n_F32(192)), vmulq_F32(s1, s1),
//                      vbslq_F32(c, vmulq_F32(vfmaq_F32(s2, s2, j), s1), vfmaq_F32(k, k, j)));
// }

// // computes silu x/(1+exp(-x)) in single precision vector
// inline static float32x4_t ggml_v_silu(float32x4_t x) {
//     const float32x4_t one = vdupq_n_F32(1.0f);
//     const float32x4_t zero = vdupq_n_F32(0.0f);
//     const float32x4_t neg_x = vsubq_F32(zero, x);
//     const float32x4_t exp_neg_x = ggml_v_expf(neg_x);
//     const float32x4_t one_plus_exp_neg_x = vaddq_F32(one, exp_neg_x);
//     return vdivq_F32(x, one_plus_exp_neg_x);
// }

// #elif defined(__AVX512F__) && defined(__AVX512DQ__)

// // adapted from arm limited optimized routine
// // the maximum error is 1.45358 plus 0.5 ulps
// // numbers above 88.38 will flush to infinity
// // numbers beneath -103.97 will flush to zero
// inline static __m512 ggml_v_expf(__m512 x) {
//   const __m512 r = _mm512_set1_ps(0x1.8p23f);
//   const __m512 z = _mm512_fmadd_ps(x, _mm512_set1_ps(0x1.715476p+0f), r);
//   const __m512 n = _mm512_sub_ps(z, r);
//   const __m512 b = _mm512_fnmadd_ps(n, _mm512_set1_ps(0x1.7f7d1cp-20f),
//                                     _mm512_fnmadd_ps(n, _mm512_set1_ps(0x1.62e4p-1f), x));
//   const __m512i e = _mm512_slli_epi32(_mm512_castps_si512(z), 23);
//   const __m512 k = _mm512_castsi512_ps(_mm512_add_epi32(e, _mm512_castps_si512(_mm512_set1_ps(1))));
//   const __mmask16 c = _mm512_cmp_ps_mask(_mm512_abs_ps(n), _mm512_set1_ps(126), _CMP_GT_OQ);
//   const __m512 u = _mm512_mul_ps(b, b);
//   const __m512 j = _mm512_fmadd_ps(_mm512_fmadd_ps(_mm512_fmadd_ps(_mm512_set1_ps(0x1.0e4020p-7f), b,
//                                                                    _mm512_set1_ps(0x1.573e2ep-5f)), u,
//                                                    _mm512_fmadd_ps(_mm512_set1_ps(0x1.555e66p-3f), b,
//                                                                    _mm512_set1_ps(0x1.fffdb6p-2f))),
//                                    u, _mm512_mul_ps(_mm512_set1_ps(0x1.ffffecp-1f), b));
//   if (_mm512_kortestz(c, c))
//     return _mm512_fmadd_ps(j, k, k);
//   const __m512i g = _mm512_and_si512(
//       _mm512_movm_epi32(_mm512_cmp_ps_mask(n, _mm512_setzero_ps(), _CMP_LE_OQ)),
//       _mm512_set1_epi32(0x82000000u));
//   const __m512 s1 =
//       _mm512_castsi512_ps(_mm512_add_epi32(g, _mm512_set1_epi32(0x7f000000u)));
//   const __m512 s2 = _mm512_castsi512_ps(_mm512_sub_epi32(e, g));
//   const __mmask16 d =
//       _mm512_cmp_ps_mask(_mm512_abs_ps(n), _mm512_set1_ps(192), _CMP_GT_OQ);
//   return _mm512_mask_blend_ps(
//       d, _mm512_mask_blend_ps(
//           c, _mm512_fmadd_ps(k, j, k),
//           _mm512_mul_ps(_mm512_fmadd_ps(s2, j, s2), s1)),
//       _mm512_mul_ps(s1, s1));
// }

// // computes silu x/(1+exp(-x)) in single precision vector
// inline static __m512 ggml_v_silu(__m512 x) {
//     const __m512 one = _mm512_set1_ps(1);
//     const __m512 zero = _mm512_setzero_ps();
//     const __m512 neg_x = _mm512_sub_ps(zero, x);
//     const __m512 exp_neg_x = ggml_v_expf(neg_x);
//     const __m512 one_plus_exp_neg_x = _mm512_add_ps(one, exp_neg_x);
//     return _mm512_div_ps(x, one_plus_exp_neg_x);
// }

// #elif defined(__AVX2__) && defined(__FMA__)

// // adapted from arm limited optimized routine
// // the maximum error is 1.45358 plus 0.5 ulps
// // numbers above 88.38 will flush to infinity
// // numbers beneath -103.97 will flush to zero
// inline static __m256 ggml_v_expf(__m256 x) {
//   const __m256 r = _mm256_set1_ps(0x1.8p23f);
//   const __m256 z = _mm256_fmadd_ps(x, _mm256_set1_ps(0x1.715476p+0f), r);
//   const __m256 n = _mm256_sub_ps(z, r);
//   const __m256 b = _mm256_fnmadd_ps(n, _mm256_set1_ps(0x1.7f7d1cp-20f),
//                                     _mm256_fnmadd_ps(n, _mm256_set1_ps(0x1.62e4p-1f), x));
//   const __m256i e = _mm256_slli_epi32(_mm256_castps_si256(z), 23);
//   const __m256 k = _mm256_castsi256_ps(
//       _mm256_add_epi32(e, _mm256_castps_si256(_mm256_set1_ps(1))));
//   const __m256i c = _mm256_castps_si256(
//       _mm256_cmp_ps(_mm256_andnot_ps(_mm256_set1_ps(-0.f), n),
//                     _mm256_set1_ps(126), _CMP_GT_OQ));
//   const __m256 u = _mm256_mul_ps(b, b);
//   const __m256 j = _mm256_fmadd_ps(_mm256_fmadd_ps(_mm256_fmadd_ps(_mm256_set1_ps(0x1.0e4020p-7f), b,
//                                                                    _mm256_set1_ps(0x1.573e2ep-5f)), u,
//                                                    _mm256_fmadd_ps(_mm256_set1_ps(0x1.555e66p-3f), b,
//                                                                    _mm256_set1_ps(0x1.fffdb6p-2f))),
//                                    u, _mm256_mul_ps(_mm256_set1_ps(0x1.ffffecp-1f), b));
//   if (!_mm256_movemask_ps(_mm256_castsi256_ps(c)))
//     return _mm256_fmadd_ps(j, k, k);
//   const __m256i g = _mm256_and_si256(
//       _mm256_castps_si256(_mm256_cmp_ps(n, _mm256_setzero_ps(), _CMP_LE_OQ)),
//       _mm256_set1_epi32(0x82000000u));
//   const __m256 s1 =
//       _mm256_castsi256_ps(_mm256_add_epi32(g, _mm256_set1_epi32(0x7f000000u)));
//   const __m256 s2 = _mm256_castsi256_ps(_mm256_sub_epi32(e, g));
//   const __m256i d = _mm256_castps_si256(
//       _mm256_cmp_ps(_mm256_andnot_ps(_mm256_set1_ps(-0.f), n),
//                     _mm256_set1_ps(192), _CMP_GT_OQ));
//   return _mm256_or_ps(
//       _mm256_and_ps(_mm256_castsi256_ps(d), _mm256_mul_ps(s1, s1)),
//       _mm256_andnot_ps(
//           _mm256_castsi256_ps(d),
//           _mm256_or_ps(
//               _mm256_and_ps(_mm256_castsi256_ps(c),
//                             _mm256_mul_ps(_mm256_fmadd_ps(s2, j, s2), s1)),
//               _mm256_andnot_ps(_mm256_castsi256_ps(c), _mm256_fmadd_ps(k, j, k)))));
// }

// // computes silu x/(1+exp(-x)) in single precision vector
// inline static __m256 ggml_v_silu(__m256 x) {
//     const __m256 one = _mm256_set1_ps(1);
//     const __m256 zero = _mm256_setzero_ps();
//     const __m256 neg_x = _mm256_sub_ps(zero, x);
//     const __m256 exp_neg_x = ggml_v_expf(neg_x);
//     const __m256 one_plus_exp_neg_x = _mm256_add_ps(one, exp_neg_x);
//     return _mm256_div_ps(x, one_plus_exp_neg_x);
// }

// #elif defined(__SSE2__) // __AVX2__ / __ARM_NEON

// #if defined(__FMA__)
// #define MADD128(x, y, z) _mm_fmadd_ps(x, y, z)
// #define NMADD128(x, y, z) _mm_fnmadd_ps(x, y, z)
// #else
// #define MADD128(x, y, z) _mm_add_ps(_mm_mul_ps(x, y), z)
// #define NMADD128(x, y, z) _mm_sub_ps(z, _mm_mul_ps(x, y))
// #endif

// // adapted from arm limited optimized routine
// // the maximum error is 1.45358 plus 0.5 ulps
// // numbers above 88.38 will flush to infinity
// // numbers beneath -103.97 will flush to zero
// inline static __m128 ggml_v_expf(__m128 x) {
//     const __m128 r = _mm_set1_ps(0x1.8p23f);
//     const __m128 z = MADD128(x, _mm_set1_ps(0x1.715476p+0f), r);
//     const __m128 n = _mm_sub_ps(z, r);
//     const __m128 b =
//         NMADD128(n, _mm_set1_ps(0x1.7f7d1cp-20f), NMADD128(n, _mm_set1_ps(0x1.62e4p-1f), x));
//     const __m128i e = _mm_slli_epi32(_mm_castps_si128(z), 23);
//     const __m128 k = _mm_castsi128_ps(_mm_add_epi32(e, _mm_castps_si128(_mm_set1_ps(1))));
//     const __m128i c =
//         _mm_castps_si128(_mm_cmpgt_ps(_mm_andnot_ps(_mm_set1_ps(-0.f), n), _mm_set1_ps(126)));
//     const __m128 u = _mm_mul_ps(b, b);
//     const __m128 j =
//         MADD128(MADD128(MADD128(_mm_set1_ps(0x1.0e4020p-7f), b, _mm_set1_ps(0x1.573e2ep-5f)), u,
//                         MADD128(_mm_set1_ps(0x1.555e66p-3f), b, _mm_set1_ps(0x1.fffdb6p-2f))),
//                 u, _mm_mul_ps(_mm_set1_ps(0x1.ffffecp-1f), b));
//     if (!_mm_movemask_epi8(c))
//         return MADD128(j, k, k);
//     const __m128i g = _mm_and_si128(_mm_castps_si128(_mm_cmple_ps(n, _mm_setzero_ps())),
//                                     _mm_set1_epi32(0x82000000u));
//     const __m128 s1 = _mm_castsi128_ps(_mm_add_epi32(g, _mm_set1_epi32(0x7f000000u)));
//     const __m128 s2 = _mm_castsi128_ps(_mm_sub_epi32(e, g));
//     const __m128i d =
//         _mm_castps_si128(_mm_cmpgt_ps(_mm_andnot_ps(_mm_set1_ps(-0.f), n), _mm_set1_ps(192)));
//     return _mm_or_ps(
//         _mm_and_ps(_mm_castsi128_ps(d), _mm_mul_ps(s1, s1)),
//         _mm_andnot_ps(_mm_castsi128_ps(d),
//                       _mm_or_ps(_mm_and_ps(_mm_castsi128_ps(c), _mm_mul_ps(MADD128(s2, j, s2), s1)),
//                                 _mm_andnot_ps(_mm_castsi128_ps(c), MADD128(k, j, k)))));
// }

// // computes silu x/(1+exp(-x)) in single precision vector
// inline static __m128 ggml_v_silu(__m128 x) {
//     const __m128 one = _mm_set1_ps(1);
//     const __m128 zero = _mm_setzero_ps();
//     const __m128 neg_x = _mm_sub_ps(zero, x);
//     const __m128 exp_neg_x = ggml_v_expf(neg_x);
//     const __m128 one_plus_exp_neg_x = _mm_add_ps(one, exp_neg_x);
//     return _mm_div_ps(x, one_plus_exp_neg_x);
// }

// #endif // __ARM_NEON / __AVX2__ / __SSE2__

// static void NN_silu_F32(const int n, float *y, const float *x) {
//     int i = 0;
// #if defined(__AVX512F__) && defined(__AVX512DQ__)
//     for (; i + 15 < n; i += 16) {
//         _mm512_storeu_ps(y + i, ggml_v_silu(_mm512_loadu_ps(x + i)));
//     }
// #elif defined(__AVX2__) && defined(__FMA__)
//     for (; i + 7 < n; i += 8) {
//         _mm256_storeu_ps(y + i, ggml_v_silu(_mm256_loadu_ps(x + i)));
//     }
// #elif defined(__SSE2__)
//     for (; i + 3 < n; i += 4) {
//         _mm_storeu_ps(y + i, ggml_v_silu(_mm_loadu_ps(x + i)));
//     }
// #elif defined(__ARM_NEON) && defined(__aarch64__)
//     for (; i + 3 < n; i += 4) {
//         vst1q_F32(y + i, ggml_v_silu(vld1q_F32(x + i)));
//     }
// #endif
//     for (; i < n; i += 1) {
//         y[i] = ggml_silu_F32(x[i]);
//     }
// }


// inline static float ggml_silu_backward_F32(float x, float dy) {
//     const float s = 1.0f/(1.0f + expf(-x));
//     return dy*s*(1.0f + x*(1.0f - s));
// }

// inline static void NN_silu_backward_F32(const int n, float *dx, const float *x, const float *dy) {
//     for (int i = 0; i < n; i += 1) {
//         dx[i] = ggml_silu_backward_F32(x[i], dy[i]);
//     }
// }
// inline static void NN_argmax_F32(const int n, int * s, const float *x) {
//     float max = -INFINITY;
//     int idx = 0;
//     for (int i = 0; i < n; i += 1) {
//         max = MAX(max, x[i]);
//         if (max == x[i]) { idx = i; }
//     }
//     *s = idx;
// }


#endif // __NN_MATH_H
