#ifndef _AOR2P_SIMDIP_MUL_H_
#define _AOR2P_SIMDIP_MUL_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_MUL
multiply every pixel of image by constant
*/

// simd, multiply by constant, 8 bits per channel, pipeline
void simd_mul_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, multiply by constant, 8 bits per channel, no pipeline
void simd_mul_8bpc_npl(imgfile_t*, uint8_t);

// no simd, multiply by constant, 8 bits per channel, no pipeline
void mul_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_MUL_H_
