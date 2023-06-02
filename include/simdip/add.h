#ifndef _SIMDIP_ADD_H
#define _SIMDIP_ADD_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_ADD
add a constant to every pixel in the image
*/

// simd, add constant, .bmp, 8 bits per channel, pipeline
void simd_add_bmp_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, add constant, .bmp, 8 bits per channel, no pipeline
void simd_add_bmp_8bpc_npl(imgfile_t*, uint8_t);

// no simd, add constant, .bmp, 8 bits per channel, no pipeline
void add_bmp_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_ADD_H
