#ifndef __NN_MINIMUM_H
#define __NN_MINIMUM_H

#include <stddef.h>
#include <stdint.h>

#include "float16.h"


void NN_minimum_i8(size_t n,
    int8_t *y, size_t incy,
    const int8_t *x1, size_t incx1,
    const int8_t *x2, size_t incx2
    );

void NN_minimum_i16(size_t n,
    int16_t *y, size_t incy,
    const int16_t *x1, size_t incx1,
    const int16_t *x2, size_t incx2
    );

void NN_minimum_i32(size_t n,
    int32_t *y, size_t incy,
    const int32_t *x1, size_t incx1,
    const int32_t *x2, size_t incx2
    );

void NN_minimum_f16(size_t n,
    float16_t *y, size_t incy,
    const float16_t *x1, size_t incx1,
    const float16_t *x2, size_t incx2
    );

void NN_minimum_f32(size_t n,
    float *y, size_t incy,
    const float *x1, size_t incx1,
    const float *x2, size_t incx2
    );


#endif // __NN_MINIMUM_H
