#ifndef _SIMDIP_MUL_H
#define _SIMDIP_MUL_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_MUL
multiply every pixel of image by constant
*/

// simd, multiply by constant, .bmp, 8 bits per channel, pipeline
void simd_mul_bmp_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, multiply by constant, .bmp, 8 bits per channel, no pipeline
void simd_mul_bmp_8bpc_npl(imgfile_t*, uint8_t);

// no simd, multiply by constant, .bmp, 8 bits per channel, no pipeline
void mul_bmp_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_MUL_H
