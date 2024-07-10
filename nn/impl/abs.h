#ifndef __NN__ABS_H
#define __NN__ABS_H

#include <stddef.h>
#include <stdint.h>
#include <math.h>

#include "nn_float16.h"


void NN__abs_i8(size_t n,
    int8_t *y, size_t incy,
    int8_t *x, size_t incx
    );

void NN__abs_i16(size_t n,
    int16_t *y, size_t incy,
    int16_t *x, size_t incx
    );

void NN__abs_i32(size_t n,
    int32_t *y, size_t incy,
    int32_t *x, size_t incx
    );

void NN__abs_f16(size_t n,
    float16_t *y, size_t incy,
    float16_t *x, size_t incx
    );

void NN__abs_f32(size_t n,
    float *y, size_t incy,
    float *x, size_t incx
    );


#endif // __NN__ABS_H
