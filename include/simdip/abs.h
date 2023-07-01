#ifndef _AOR2P_SIMDIP_ABS_H_
#define _AOR2P_SIMDIP_ABS_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_ABS
absolute value of every pixel in the image
*/

// simd, absolute value, 8 bits per channel, pipeline
void simd_abs_8bpc(uint8_t*, uint8_t*, uint8_t*);

// simd, absolute value, 8 bits per channel, no pipeline
void simd_abs_8bpc_npl(imgfile_t*);

// no simd, absolute value, 8 bits per channel, no pipeline
void abs_8bpc_npl(imgfile_t*);

#endif//_AOR2P_SIMDIP_ABS_H_
