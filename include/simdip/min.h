#ifndef _SIMDIP_MIN_H
#define _SIMDIP_MIN_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_MIN
replace pixel with minimum value of pixel and constant
*/

// simd, replace pixel with minimum of pixel and constant, .bmp, 8 bits per channel, pipeline
void simd_min_bmp_8bpc(__m256i*, __m256i*, __m256i*, uint8_t);

// simd, replace pixel with minimum of pixel and constant, .bmp, 8 bits per channel, no pipeline
void simd_min_bmp_8bpc_npl(imgfile_t*, uint8_t);

// no simd, replace pixel with minimum of pixel and constant, .bmp, 8 bits per channel, no pipeline
void min_bmp_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_MIN_H
