#include <stdio.h>
#include <string.h>
#include "fp16.h"

#define FP32_BIAS   (127)
#define FP16_BIAS   (15)
#define BIAS_32TO16 (FP32_BIAS - FP16_BIAS)

#define FP32_BIT_SIGN (31)
#define FP32_BIT_EXP  (23)
#define FP16_BIT_SIGN (15)
#define FP16_BIT_EXP  (10)

#define FP16_CONCAT(s, e, f) \
    (((s & 0x1) << FP16_BIT_SIGN) | ((e & 0x1f) << FP16_BIT_EXP) | (f & 0x3ff))

#define FP16_NAN     (0xffff)
#define FP16_ZERO(s) FP16_CONCAT(s, 0, 0)
#define FP16_INF(s)  FP16_CONCAT(s, 0x1f, 0)


/*
 * https://en.wikipedia.org/wiki/Half-precision_floating-point_format
 */
FP16_t get_fp16(float f)
{
    FP32_t bin32;
    FP16_t sign, exp, frac;

    // convert each parts
    memcpy(&bin32, &f, sizeof(bin32));
    sign = (FP16_t)((bin32 & 0x80000000) >> (FP32_BIT_SIGN));
    exp  = (FP16_t)((bin32 & 0x7F800000) >> (FP32_BIT_EXP));
    frac = (FP16_t)((bin32 & 0x007FFFFF) >> (FP32_BIT_EXP - FP16_BIT_EXP)); // use upper 10 bits.

    // return special value
    if (exp == 0x00 && frac == 0x0000)
        return FP16_ZERO(sign);
    else if (exp == 0xff)
        return (frac == 0x0000) ? FP16_INF(sign) : FP16_NAN;

    // exponent encoding
    if (exp < BIAS_32TO16)
        exp = 0x00; // lower limit
    else if ((exp - 0x1f) > BIAS_32TO16)
        exp = 0x1f; // upper limit
    else
        exp -= BIAS_32TO16;

    return FP16_CONCAT(sign, exp, frac);
}
