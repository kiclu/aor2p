#ifndef _AOR2P_SIMDIP_GS_H_
#define _AOR2P_SIMDIP_GS_H_

#include<immintrin.h>
#include<imgparse/imgfile.h>

/*
OP_GS
convert image to grayscale
*/

// simd, convert to grayscale, 8 bits per channel, pipeline
void simd_gs_8bpc(uint8_t*, uint8_t*, uint8_t*);

// simd, convert to grayscale, 8 bits per channel, no pipeline
void simd_gs_8bpc_npl(imgfile_t*);

// no simd, convert to grayscale, 8 bits per channel, no pipeline
void gs_8bpc_npl(imgfile_t*);

#endif//_AOR2P_SIMDIP_GS_H_
