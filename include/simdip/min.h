#ifndef _AOR2P_SIMDIP_MIN_H_
#define _AOR2P_SIMDIP_MIN_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_MIN
replace every pixel of image with minimum its value and constant
*/

// simd, min, 8 bits per channel, pipeline
void simd_min_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, min, 8 bits per channel, no pipeline
void simd_min_8bpc_npl(imgfile_t*, uint8_t);

// no simd, min, 8 bits per channel, no pipeline
void min_8bpc_npl(imgfile_t*, uint8_t);

#endif//_AOR2P_SIMDIP_MIN_H_
