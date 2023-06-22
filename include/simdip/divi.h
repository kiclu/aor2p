#ifndef _SIMDIP_DIVI_H
#define _SIMDIP_DIVI_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_DIVI
divide constant by every pixel in the image
*/

// simd, divide constant by pixel, 8 bits per channel, pipeline
void simd_divi_8bpc(uint8_t*, uint8_t*, uint8_t*, uint8_t);

// simd, divide constant by pixel, 8 bits per channel, no pipeline
void simd_divi_8bpc_npl(imgfile_t*, uint8_t);

// no simd, divide constant by pixel, 8 bits per channel, no pipeline
void divi_8bpc_npl(imgfile_t*, uint8_t);

#endif//_SIMDIP_DIVI_H
