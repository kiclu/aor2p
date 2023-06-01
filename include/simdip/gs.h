#ifndef _SIMDIP_GS_H
#define _SIMDIP_GS_H

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_GS
convert image to grayscale
*/

// simd, convert to grayscale, .bmp, 8 bits per channel, pipeline
void simd_gs_bmp_8bpc(uint8_t*, uint8_t*, uint8_t*);

// simd, convert to grayscale, .bmp, 8 bits per channel, no pipeline
void simd_gs_bmp_8bpc_npl(imgfile_t*);

// no simd, convert to grayscale, .bmp, 8 bits per channel, no pipeline
void gs_bmp_8bpc_npl(imgfile_t*);

#endif//_SIMDIP_GS_H
