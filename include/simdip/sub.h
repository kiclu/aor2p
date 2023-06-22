#ifndef _SIMDIP_SUB_H
#define _SIMDIP_SUB_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_SUB
subtract a constant from every pixel in the image
*/

// simd, sub constant, 8 bits per channel, pipeline
void simd_sub_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, sub constant, 8 bits per channel, no pipeline
void simd_sub_8bpc_npl(imgfile_t*, uint8_t);

// no simd, sub constant, 8 bits per channel, no pipeline
void sub_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_SUB_H
