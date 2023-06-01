#ifndef _SIMDIP_ABS_H
#define _SIMDIP_ABS_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_ABS
absolute value of every pixel in the image
*/

// simd, absolute value, .bmp, 8 bits per channel, pipeline
void simd_abs_bmp_8bpc(__m256i*, __m256i*, __m256i*);

// simd, absolute value, .bmp, 8 bits per channel, no pipeline
void simd_abs_bmp_8bpc_npl(imgfile_t*);

// no simd, absolute value, .bmp, 8 bits per channel, no pipeline
void abs_bmp_8bpc_npl(imgfile_t*);

#endif//_SIMDIP_ABS_H
