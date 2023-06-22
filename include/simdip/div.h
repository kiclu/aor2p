#ifndef _SIMDIP_DIV_H
#define _SIMDIP_DIV_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_DIV
divide every pixel in the image by constant
*/

// simd, divide by constant, 8 bits per channel, pipeline
void simd_div_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, divide by constant, 8 bits per channel, no pipeline
void simd_div_8bpc_npl(imgfile_t*, uint8_t);

// no simd, divide by constant, 8 bits per channel, no pipeline
void div_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_DIV_H
