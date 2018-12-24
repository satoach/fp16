#ifndef __MY_FP16_h__
#define __MY_FP16_h__
#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int FP32_t;
typedef unsigned short FP16_t;

FP16_t get_fp16(float f);

#ifdef __cplusplus
}
#endif
#endif /* __MY_FP16_h__ */
