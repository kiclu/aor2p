#ifndef _SIMDIP_MIN_H
#define _SIMDIP_MIN_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_MIN
replace every pixel of image with minimum its value and constant
*/

// simd, min, .bmp, 8 bits per channel, pipeline
void simd_min_bmp_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, min, .bmp, 8 bits per channel, no pipeline
void simd_min_bmp_8bpc_npl(imgfile_t*, uint8_t);

// no simd, min, .bmp, 8 bits per channel, no pipeline
void min_bmp_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_MIN_H
