#ifndef _SIMDIP_ADDS_H
#define _SIMDIP_ADDS_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_ADDS
add a constant to every pixel in the image, saturate at 255
*/

// simd, add constant, 8 bits per channel, pipeline
void simd_adds_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, add constant, 8 bits per channel, no pipeline
void simd_adds_8bpc_npl(imgfile_t*, uint8_t);

// no simd, add constant, 8 bits per channel, no pipeline
void adds_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_ADDS_H
