#ifndef _SIMDIP_DIV_H
#define _SIMDIP_DIV_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_DIV
divide every pixel in the image by constant
*/

// simd, divide by constant, .bmp, 8 bits per channel, pipeline
void simd_div_bmp_8bpc(__m256i*, __m256i*, __m256i*, uint8_t);

// simd, divide by constant, .bmp, 8 bits per channel, no pipeline
void simd_div_bmp_8bpc_npl(imgfile_t*, uint8_t);

// no simd, divide by constant, .bmp, 8 bits per channel, no pipeline
void div_bmp_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_DIV_H
