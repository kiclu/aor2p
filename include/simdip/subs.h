#ifndef _SIMDIP_SUBS_H
#define _SIMDIP_SUBS_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_SUBS
subtract constant from every pixel in the image, saturate at 0
*/

// simd, subtract constant from pixel, 8 bits per channel, pipeline
void simd_subs_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, subtract constant from pixel, 8 bits per channel, no pipeline
void simd_subs_8bpc_npl(imgfile_t*, uint8_t);

// no simd, subtract constant from pixel, 8 bits per channel, no pipeline
void subs_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_SUBS_H
