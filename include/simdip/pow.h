#ifndef _SIMDIP_POW_H
#define _SIMDIP_POW_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_POW
raise every pixel of image to power of constant
*/

// simd, pow, 8 bits per channel, pipeline
void simd_pow_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, pow, 8 bits per channel, no pipeline
void simd_pow_8bpc_npl(imgfile_t*, uint8_t);

// no simd, pow, 8 bits per channel, no pipeline
void pow_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_POW_H
