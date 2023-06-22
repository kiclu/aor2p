#ifndef _SIMDIP_MAX_H
#define _SIMDIP_MAX_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_MAX
replace every pixel of image with maximum its value and constant
*/

// simd, max, 8 bits per channel, pipeline
void simd_max_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, max, 8 bits per channel, no pipeline
void simd_max_8bpc_npl(imgfile_t*, uint8_t);

// no simd, max, 8 bits per channel, no pipeline
void max_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_MAX_H
